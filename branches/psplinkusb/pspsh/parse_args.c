/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * parse_args.c - PSPLINK argument parser code
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/psplink/parse_args.c $
 * $Id: parse_args.c 2026 2006-10-14 13:09:48Z tyranid $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parse_args.h"

int hex_to_int(char ch)
{
	ch = toupper(ch);
	if((ch >= '0') && (ch <= '9'))
	{
		return ch-'0';
	}
	else if((ch >= 'A') && (ch <= 'F'))
	{
		return ch-'A';
	}
	
	return 0;
}

int oct_to_int(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return ch-'0';
	}

	return 0;
}

int isodigit(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return 1;
	}

	return 0;
}

int decode_hex(const char *str, unsigned char *ch)
{
	int i;

	*ch = 0;
	for(i = 0; i < 2; i++)
	{
		if(!isxdigit(str[i]))
		{
			break;
		}
		*ch = *ch << 4;
		*ch = *ch | hex_to_int(str[i]);
	}
	if(i == 0)
	{
		printf("Missing following hex characters\n");
		return 0;
	}
	if(*ch == 0)
	{
		printf("Invalid hex character (not allowed NULs)\n");
		return 0;
	}

	return i;
}

int decode_oct(const char *str, unsigned char *ch)
{
	int i;

	*ch = 0;
	for(i = 0; i < 4; i++)
	{
		if(!isodigit(str[i]))
		{
			break;
		}
		*ch = *ch << 3;
		*ch = *ch | oct_to_int(str[i]);
	}
	if(i == 0)
	{
		printf("Missing following octal characters\n");
		return 0;
	}
	if(*ch == 0)
	{
		printf("Invalid octal character (not allowed NULs)\n");
		return 0;
	}

	return i;
}

const char *parse_redir(const char *in, char *filename, int *type)
{
	while(isspace(*in))
	{
		in++;
	}

	if(*in == '>')
	{
		in++;
		if(*in == '>')
		{
			in++;
			*type = REDIR_TYPE_CAT;
		}
		else
		{
			*type = REDIR_TYPE_NEW;
		}

		if((*in == '>') || (*in == 0))
		{
			fprintf(stderr, "Invalid redirection prefix (no filename)\n");
			return NULL;
		}
	}

	return in;
}

/* Read a single string from the output, escape characters and quotes, insert $ args */
int read_string(const char **pin, char **pout, int sargc, const struct SArg *sargv)
{
	int in_quote = 0;
	const char *in = *pin;
	char *out = *pout;
	int len = 0;
	int error = 0;

	while(isspace(*in))
	{
		in++;
	}

	if(*in == 0)
	{
		*pin = in;
		return 0;
	}

	while((*in != 0) && (error == 0))
	{
		/* Escape character */
		if(*in == '\\')
		{
			if(in_quote == '\'')
			{
				*out++ = *in++;
				if(*in)
				{
					*out++ = *in++;
				}
			}
			else
			{
				/* Skip the escape */
				in++;
				switch(*in)
				{
					case 'n': *out++ = 10;
							  in++;
							  break;
					case 'r': *out++ = 13;
							  in++;
							  break;
					case '0': /* Octal */
							  {
								  int i;
								  unsigned char ch;
								  in++;
								  i = decode_oct(in, &ch);
								  if((i == 0) || (i == 1))
								  {
									  error = 1;
									  break;
								  }
								  in += i;
								  *out++ = ch;
							  }
							  break;
					case 'x': /* Hexadecimal */
							  {
								  int i;
								  unsigned char ch;
								  in++;
								  i = decode_hex(in, &ch);
								  if((i == 0) || (i == 1))
								  {
									  error = 1;
									  break;
								  }
								  in += i;
								  *out++ = ch;
							  }
							  break;
					case 0  : break; /* End of string */
					default : *out++ = *in++;
							  break;
				};
			}
		}
		else
		{
			if((isspace(*in)) && (in_quote == 0))
			{
				while(isspace(*in))
				{
					in++;
				}
				break;
			}
			else if((*in == '>') && (in_quote == 0))
			{
				break;
			}
			else if((*in == '"') || (*in == '\''))
			{
				if(in_quote)
				{
					if(*in == in_quote)
					{
						in_quote = 0;
						in++;
					}
					else
					{
						*out++ = *in++;
					}
				}
				else
				{
					in_quote = *in;
					in++;
				}
			}
			else
			{
				*out++ = *in++;
			}
		}
	}

	if(in_quote)
	{
		printf("Missing matching quote %c\n", in_quote);
	}
	else if(error)
	{
		printf("Error in command line\n");
	}
	else
	{
		*out++ = 0;
		len = out - *pout;
	}

	*pin = in;
	*pout = out;
	return len;
}

int parse_cli(const char *in, char *out, int *argc, char **argv, int max_args, int sargc, const struct SArg *sargv, int *type, char *redir)
{
	char *lastout;
	char *outstart = out;

	if((in == NULL) || (out == NULL) || (argc == NULL) || (argv == NULL) || (max_args <= 0) || (type == NULL) || (redir == NULL))
	{
		printf("Error in parse_args, invalid arguments\n");
		return 0;
	}

	*argc = 0;
	*type = REDIR_TYPE_NONE;

	/* Skip any leading white space */
	while(isspace(*in))
	{
		in++;
	}

	lastout = out;
	while(*argc < (max_args-1))
	{
		/* Parse shell characters */
		if(*in == '>')
		{
			char *outfile = redir;

			in++;
			if(*in == '>')
			{
				*type = REDIR_TYPE_CAT;
				in++;
			}
			else
			{
				*type = REDIR_TYPE_NEW;
			}

			if(read_string(&in, &outfile, sargc, sargv) == 0)
			{
				printf("Error in redirection, no filename\n");
				return 0;
			}
		}
		else
		{
			if(read_string(&in, &out, sargc, sargv) == 0)
			{
				break;
			}

			argv[*argc] = lastout;
			*argc += 1;
			lastout = out;
		}
	}

	argv[*argc] = NULL;
	/* A command ends with a 1 */
	*out++ = 1;

	return out-outstart;
}

#ifdef _TEST
int main(void)
{
	char str[1024];
	char out[1024];

	while(fgets(str, sizeof(str), stdin))
	{
		char *argv[16];
		char redir[1025];
		int  type = 0;
		int  argc;
		int binlen;

		binlen = parse_cli(str, out, &argc, argv, 16, 0, NULL, &type, redir);
		if(binlen > 0)
		{
			int i;
			for(i = 0; i < argc; i++)
			{
				printf("Arg %d: '%s'\n", i, argv[i]);
			}

			for(i = 0; i < binlen; i++)
			{
				if(out[i] < 32)
				{
					printf("\\x%02X", out[i]);
				}
				else
				{
					printf("%c", out[i]);
				}
			}
			printf("\n");
			if(type > 0)
			{
				printf("Redir type %d, '%s'\n", type, redir);
			}
		}
	}
}
#endif
