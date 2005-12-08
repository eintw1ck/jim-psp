/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * socket.c - Socket wrappers to provide similar functions to normal unix
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * 
 */
#include <errno.h>
#include <sys/socket.h>

#include <psptypes.h>

#define __PSP_SOCKET_MAX 1024
extern char __psp_socket_map[__PSP_SOCKET_MAX];

#ifdef F___psp_socket_map
char __psp_socket_map[__PSP_SOCKET_MAX];
#endif

#ifdef F_socket
int	socket(int domain, int type, int protocol)
{
	int sock;
	int i;

	sock = sceNetInetSocket(domain, type, protocol);
	if(sock < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	if((sock >= 0) && (sock < __PSP_SOCKET_MAX))
	{
		__psp_socket_map[sock] = 1;
	}
	else
	{
		sceNetInetClose(sock);
		errno = ENOENT;
		return -1;
	}

	return sock | SOCKET_FD_PAT;
}
#endif

#ifdef F_accept
int	accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
	int sock;
	int new;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	new = sceNetInetAccept(sock, addr, addrlen);
	if((new >= 0) && (new < __PSP_SOCKET_MAX))
	{
		__psp_socket_map[new] = 1;
	}
	else
	{
		sceNetInetClose(new);
		errno = ENOENT;
		return -1;
	}

	return new | SOCKET_FD_PAT;
}
#endif

#ifdef F_bind
int	bind(int s, const struct sockaddr *my_addr, socklen_t addrlen)
{
	int ret;
	int sock;
	
	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetBind(sock, my_addr, addrlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_connect
int	connect(int s, const struct sockaddr *serv_addr, socklen_t addrlen)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetConnect(sock, serv_addr, addrlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_setsockopt
int	getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetGetsockopt(sock, level, optname, optval, optlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_listen
int	listen(int s, int backlog)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetListen(sock, backlog);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_recv
size_t	recv(int s, void *buf, size_t len, int flags)
{
	int sock;
	int ret;

	if(sceNetInetRecv == NULL)
	{
		return -1;
	}

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetRecv(sock, buf, len, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_recvfrom
size_t	recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetRecvfrom(sock, buf, len, flags, from, fromlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_send
size_t	send(int s, const void *buf, size_t len, int flags)
{
	int sock;
	int ret;

	if(sceNetInetSend == NULL)
	{
		return -1;
	}

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSend(sock, buf, len, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_sendto
size_t	sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSendto(sock, buf, len, flags, to, tolen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_setsockopt
int	setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}
	sock = modNetFindSocket(s);
	if(sock < 0)
	{
		return -1;
	}

	ret = sceNetInetSetsockopt(sock, level, optname, optval, optlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_shutdown
int	shutdown(int s, int how)
{
	int sock;
	int ret;

	if(!(SOCKET_IS_VALID(s)))
	{
		errno = EBADF;
		return -1;
	}

	sock = SOCKET_GET_SOCK(s);

	if(__psp_socket_map[sock] == 0)
	{
		errno = EBADF;
		return -1;
	}
	sock = modNetFindSocket(s);
	if(sock < 0)
	{
		return -1;
	}

	ret = sceNetInetShutdown(sock, how);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif
