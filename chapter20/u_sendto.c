#include <errno.h>
#include <sys/socket.h>
#include "uiciname.h"
#include "uiciudp.h"

ssize_t u_sendto(int fd, void *buf, size_t nbytes, u_buf_t *ubufp) {
   int len;
   struct sockaddr *remotep;
   int retval;

   len = sizeof(struct sockaddr_in);
   remotep = (struct sockaddr *)ubufp;
   while (((retval = sendto(fd, buf, nbytes, 0, remotep, len)) == -1) &&
           (errno == EINTR)) ;  
   return retval;
}

ssize_t u_sendtohost(int fd, void *buf, size_t nbytes, char *hostn,
                     u_port_t port) {
   struct sockaddr_in remote;

   if (name2addr(hostn, &(remote.sin_addr.s_addr)) == -1) {
      errno = EINVAL;
      return -1;
   }
   remote.sin_port = htons((short)port);
   remote.sin_family = AF_INET;
   return u_sendto(fd, buf, nbytes, &remote);
}
