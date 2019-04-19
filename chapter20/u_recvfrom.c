#include <errno.h>
#include <sys/socket.h>
#include "uiciudp.h"

ssize_t u_recvfrom(int fd, void *buf, size_t nbytes, u_buf_t *ubufp) {
   int len;
   struct sockaddr *remote;
   int retval;
 
   len = sizeof (struct sockaddr_in);
   remote = (struct sockaddr *)ubufp;
   while (((retval = recvfrom(fd, buf, nbytes, 0, remote, &len)) == -1) &&
           (errno == EINTR)) ; 
   return retval;
}
