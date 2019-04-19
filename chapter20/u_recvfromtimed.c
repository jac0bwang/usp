#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "restart.h"
#include "uiciudp.h"

ssize_t u_recvfromtimed(int fd, void *buf, size_t nbytes, u_buf_t *ubufp,
                         double seconds) {
   int len;
   struct sockaddr *remote;
   int retval;
   struct timeval timedone;
 
   timedone = add2currenttime(seconds);
   if (waitfdtimed(fd, timedone) == -1)
      return (ssize_t)(-1);
   len = sizeof (struct sockaddr_in);
   remote = (struct sockaddr *)ubufp;
   while (((retval = recvfrom(fd, buf, nbytes, 0, remote, &len)) == -1) &&
           (errno == EINTR)) ; 
   return retval;
}
