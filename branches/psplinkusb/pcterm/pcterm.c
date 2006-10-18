/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * pcterm.c - PSPLINK pc terminal
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include <shellcmd.h>

#ifndef SOL_TCP
#define SOL_TCP 6
#endif

#define DEFAULT_PORT 10000
#define HISTORY_FILE ".pcterm.hist"
#define DEFAULT_IP     "localhost"

struct Args
{
	const char *ip;
	const char *hist;
	const char *log;
	unsigned short port;
	int notty;
};

struct GlobalContext
{
	struct Args args;
	int exit;
	int conn_sanity;
	fd_set readsave;
	int sock;
	int outsock;
	int errsock;
	int log;
	char history_file[PATH_MAX];
	char currpath[PATH_MAX];
	char currcmd[PATH_MAX];
};

struct GlobalContext g_context;

int fixed_write(int s, const void *buf, int len)
{
	int written = 0;

	while(written < len)
	{
		int ret;

		ret = write(s, buf+written, len-written);
		if(ret < 0)
		{
			if(errno != EINTR)
			{
				perror("write");
				written = -1;
				break;
			}
		}
		else
		{
			written += ret;
		}
	}

	return written;
}

int execute_line(const char *buf)
{
	int len;

	len = strlen(buf);

	if(len > 0)
	{
		len = fixed_write(g_context.sock, buf, len);
		if(len < 0)
		{
			close(g_context.sock);
			g_context.sock = -1;
			return 0;
		}
	}

	len = fixed_write(g_context.sock, "\n", 1);

	if(len < 0)
	{
		close(g_context.sock);
		g_context.sock = -1;
		return 0;
	}

	return 1;
}

void cli_handler(char *buf)
{
	if((buf) && (*buf))
	{
		add_history(rl_line_buffer);
		if((strcmp(rl_line_buffer, "exit") == 0) || (strcmp(rl_line_buffer, "quit") == 0))
		{
			g_context.exit = 1;
		}
		else if(strcmp(rl_line_buffer, "close") == 0)
		{
			/* Exit without exiting the psplink shell */
			g_context.exit = 1;
			rl_callback_handler_remove();
			rl_callback_handler_install("", cli_handler);
			return;
		}
		else if(rl_line_buffer[0] == '!')
		{
			if(strncmp(&rl_line_buffer[1], "cd ", 3) == 0)
			{
				chdir(&rl_line_buffer[4]);
			}
			else
			{
				system(&rl_line_buffer[1]);
			}
			return;
		}

		/* Indicates a parameter to pass to the hostfs interpreter */
		if(rl_line_buffer[0] != '@')
		{
			/* Remove the handler and prompt */
			rl_callback_handler_remove();
			rl_callback_handler_install("", cli_handler);
		}

		execute_line(buf);
	}
}

int cli_reset()
{
	execute_line("reset");

	return 0;
}

int cli_step()
{
	execute_line("step");

	return 0;
}

int cli_skip()
{
	execute_line("skip");

	return 0;
}

int init_readline(void)
{
	rl_bind_key_in_map(META('r'), cli_reset, emacs_standard_keymap);
	rl_bind_key_in_map(META('s'), cli_step, emacs_standard_keymap);
	rl_bind_key_in_map(META('k'), cli_skip, emacs_standard_keymap);
	rl_callback_handler_install("", cli_handler);

	return 1;
}

int parse_args(int argc, char **argv, struct Args *args)
{
	memset(args, 0, sizeof(*args));
	args->port = DEFAULT_PORT;

	while(1)
	{
		int ch;
		int error = 0;

		ch = getopt(argc, argv, "np:h:l:");
		if(ch < 0)
		{
			break;
		}

		switch(ch)
		{
			case 'p': args->port = atoi(optarg);
					  break;
			case 'h': args->hist = optarg;
					  break;
			case 'l': args->log = optarg;
					  break;
			case 'n': args->notty = 1;
					  break;
			default : error = 1;
					  break;
		};

		if(error)
		{
			return 0;
		}
	}

	argc -= optind;
	argv += optind;

	if(argc < 1)
	{
		args->ip = DEFAULT_IP;
	}
	else
	{
		args->ip = argv[0];
	}

	return 1;
}

void print_help(void)
{
	fprintf(stderr, "PCTerm Help\n");
	fprintf(stderr, "Usage: pcterm [options] ipaddr\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-p port     : Specify the port number\n");
	fprintf(stderr, "-h history  : Specify the history file (default ~/%s)\n", HISTORY_FILE);
	fprintf(stderr, "-l logfile  : Write out all shell text to a log file\n");
	fprintf(stderr, "-n          : Do not connect up the tty (stdin/stdout/stderr)\n");
}

int init_sockaddr(struct sockaddr_in *name, const char *ipaddr, unsigned short port)
{
	struct hostent *hostinfo;

	name->sin_family = AF_INET;
	name->sin_port = htons(port);
	hostinfo = gethostbyname(ipaddr);
	if(hostinfo == NULL)
	{
		fprintf(stderr, "Unknown host %s\n", ipaddr);
		return 0;
	}
	name->sin_addr = *(struct in_addr *) hostinfo->h_addr;

	return 1;
}

int set_socknonblock(int sock, int block)
{
	int fopt;

	fopt = fcntl(sock, F_GETFL);
	if(block)
	{
		fopt |= O_NONBLOCK;
	}
	else
	{
		fopt &= ~O_NONBLOCK;
	}

	return fcntl(sock, F_SETFL, fopt);
}

int process_cmd(const unsigned char *str)
{
	if(*str < 128)
	{
		if(g_context.log >= 0)
		{
			write(g_context.log, str, strlen((char*) str));
		}

		printf("%s", str);
		fflush(stdout);
	}
	else
	{
		if(*str == SHELL_CMD_CWD)
		{
			snprintf(g_context.currpath, PATH_MAX, "%s", str+1);
		}
		else if((*str == SHELL_CMD_SUCCESS) || (*str == SHELL_CMD_ERROR))
		{
			char prompt[PATH_MAX];

			/* If end of command then restore prompt */
			printf("\n");
			rl_callback_handler_remove();
			snprintf(prompt, PATH_MAX, "%s> ", g_context.currpath);
			rl_callback_handler_install(prompt, cli_handler);
		}
	}

	return 1;
}

int read_socket(int sock)
{
	static unsigned char linebuf[16*1024];
	static int pos = 0;
	unsigned char buf[1024];
	unsigned char *curr;
	int len;

	len = read(sock, buf, sizeof(buf)-1);
	if(len < 0)
	{
		perror("read");
		return -1;
	}

	/* EOF */
	if(len == 0)
	{
		return -1;
	}

	buf[len] = 0;
	curr = buf;

	while(*curr)
	{
		if(*curr == SHELL_CMD_BEGIN)
		{
			/* Reset start pos, discard any data we ended up missing */
			pos = 1;
		}
		else if(*curr == SHELL_CMD_END)
		{
			if(pos > 1)
			{
				linebuf[pos-1] = 0;
				/* Found a command, process */
				process_cmd(linebuf);
				pos = 0;
			}
		}
		else
		{
			if(pos > 0)
			{
				linebuf[pos-1] = *curr;
				pos++;
			}
		}

		curr++;
	}

	return len;
}

int read_outsocket(int sock)
{
	char buf[1024];
	int len;

	len = read(sock, buf, sizeof(buf)-1);
	if(len < 0)
	{
		perror("read");
		return -1;
	}

	/* EOF */
	if(len == 0)
	{
		return -1;
	}

	buf[len] = 0;

	printf("%s", buf);

	return len;
}

int read_errsocket(int sock)
{
	char buf[1024];
	int len;

	len = read(sock, buf, sizeof(buf)-1);
	if(len < 0)
	{
		perror("read");
		return -1;
	}

	/* EOF */
	if(len == 0)
	{
		return -1;
	}

	buf[len] = 0;

	printf("%s", buf);

	return len;
}

int connect_to(const char *ipaddr, unsigned short port)
{
	int sock = -1;
	int success = 0;
	struct sockaddr_in name;

	do
	{
		if(!init_sockaddr(&name, ipaddr, port))
		{
			break;
		}
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			perror("socket");
			break;
		}

		if(connect(sock, (struct sockaddr *) &name, sizeof(name)) < 0)
		{
			perror("connect");
			break;
		}
		else
		{
			FD_SET(sock, &g_context.readsave);
		}

		success = 1;
	}
	while(0);

	if(!success)
	{
		if(sock >= 0)
		{
			close(sock);
			sock = -1;
		}
	}

	return sock;
}

void shell(void)
{
	fd_set readset;
	FD_ZERO(&g_context.readsave);

	printf("Opening connection to %s port %d\n", g_context.args.ip, g_context.args.port);
	if((g_context.sock = connect_to(g_context.args.ip, g_context.args.port)) < 0)
	{
		return;
	}

	if(g_context.args.notty == 0)
	{
		if((g_context.outsock = connect_to(g_context.args.ip, g_context.args.port+2)) < 0)
		{
			fprintf(stderr, "Could not connect to stdout channel\n");
		}
		if((g_context.errsock = connect_to(g_context.args.ip, g_context.args.port+3)) < 0)
		{
			fprintf(stderr, "Could not connect to stderr channel\n");
		}
	}

	init_readline();
	read_history(g_context.history_file);
	history_set_pos(history_length);

	FD_SET(STDIN_FILENO, &g_context.readsave);
	/* Change to the current directory, should return our path */
	write(g_context.sock, "cd .\n", strlen("cd .\n"));

	while(!g_context.exit)
	{
		int ret;

		readset = g_context.readsave;
		ret = select(FD_SETSIZE, &readset, NULL, NULL, NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("select");
			break;
		}
		else if(ret == 0)
		{
			continue;
		}
		else
		{
			if(FD_ISSET(STDIN_FILENO, &readset))
			{
				rl_callback_read_char();
			}

			if(FD_ISSET(g_context.sock, &readset))
			{
				/* Do read */
				if(read_socket(g_context.sock) < 0)
				{
					close(g_context.sock);
					g_context.sock = -1;
					break;
				}
			}

			if((g_context.outsock >= 0) && FD_ISSET(g_context.outsock, &readset))
			{
				if(read_outsocket(g_context.outsock) < 0)
				{
					FD_CLR(g_context.outsock, &g_context.readsave);
					close(g_context.outsock);
					g_context.outsock = -1;
				}
			}
			if((g_context.errsock >= 0) && FD_ISSET(g_context.errsock, &readset))
			{
				if(read_errsocket(g_context.errsock) < 0)
				{
					FD_CLR(g_context.errsock, &g_context.readsave);
					close(g_context.errsock);
					g_context.errsock = -1;
				}
			}
		}
	}

	write_history(g_context.history_file);
	rl_callback_handler_remove();
}

void sig_call(int sig)
{
	if((sig == SIGINT) || (sig == SIGTERM))
	{
		printf("Exiting\n");
		if(g_context.sock >= 0)
		{
			close(g_context.sock);
			g_context.sock = -1;
		}
		if(g_context.outsock >= 0)
		{
			close(g_context.outsock);
			g_context.outsock = -1;
		}
		if(g_context.errsock >= 0)
		{
			close(g_context.errsock);
			g_context.errsock = -1;
		}
		rl_callback_handler_remove();
		exit(0);
	}
}

void build_histfile(void)
{
	if(g_context.args.hist == NULL)
	{
		char *home;

		home = getenv("HOME");
		if(home == NULL)
		{
			snprintf(g_context.history_file, PATH_MAX, "%s", HISTORY_FILE);
		}
		else
		{
			snprintf(g_context.history_file, PATH_MAX, "%s/%s", home, HISTORY_FILE);
		}
	}
	else
	{
		snprintf(g_context.history_file, PATH_MAX, "%s", g_context.args.hist);
	}
}

int main(int argc, char **argv)
{
	memset(&g_context, 0, sizeof(g_context));
	g_context.sock = -1;
	g_context.outsock = -1;
	g_context.errsock = -1;
	g_context.log  = -1;
	if(parse_args(argc, argv, &g_context.args))
	{
		if(g_context.args.log)
		{
			g_context.log = open(g_context.args.log, O_WRONLY | O_CREAT | O_TRUNC, 0660);
			if(g_context.log < 0)
			{
				fprintf(stderr, "Warning: Could not open log file %s (%s)\n", g_context.args.log, 
						strerror(errno));
			}
		}
		build_histfile();
		shell();
		if(g_context.sock >= 0)
		{
			close(g_context.sock);
		}
		if(g_context.outsock >= 0)
		{
			close(g_context.outsock);
		}
		if(g_context.errsock >= 0)
		{
			close(g_context.errsock);
		}
		if(g_context.log >= 0)
		{
			close(g_context.log);
		}
	}
	else
	{
		print_help();
	}

	return 0;
}
