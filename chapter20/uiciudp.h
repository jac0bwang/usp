#include <netinet/in.h>

#ifndef UPORT
typedef unsigned short u_port_t;
#endif
#define UPORT

#ifndef ETIME
#define ETIME ETIMEDOUT
#endif

typedef struct sockaddr_in u_buf_t;
int u_openudp(u_port_t port);
void u_gethostname(u_buf_t *ubufp, char *hostn, int hostnsize);
void u_gethostinfo(u_buf_t *ubufp, char *info, int infosize);
int u_comparehost(u_buf_t *ubufp, char *hostn, u_port_t port);
ssize_t u_sendtohost(int fd, void *buf, size_t nbyte, char *hostn,
                     u_port_t port);
ssize_t u_sendto(int fd, void *buf, size_t nbyte, u_buf_t *ubufp);
ssize_t u_recvfrom(int fd, void *buf, size_t nbyte, u_buf_t *ubufp);
ssize_t u_recvfromtimed(int fd, void *buf, size_t nbyte, u_buf_t *ubufp,
                         double time);
int u_join(char *IP_address, u_port_t port, u_buf_t *ubufp);
int u_leave(int mcastfd, u_buf_t *ubufp);
