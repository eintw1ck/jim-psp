/* arpa/inet.h - Functions for converting IP addresses between strings and numbers */

#include <netinet/in.h>

in_addr_t sceNetInetInetAddr(const char *ip);
int sceNetInetInetAton(const char *ip, struct in_addr *in);
int sceNetInetInetNtop(int af, const void *src, char *dst, socklen_t cnt);
int sceNetInetInetPton(int af, const char *src, void *dst);

#define inet_addr sceNetInetInetAddr
#define inet_aton sceNetInetInetAton
#define inet_ntop sceNetInetInetNtop
#define inet_pton sceNetInetInetPton
