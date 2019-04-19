#include <sys/time.h>
#include "restart.h"

ssize_t readtimed(int fd, void *buf, size_t nbyte, double seconds) {
   struct timeval timedone;
 
   timedone = add2currenttime(seconds); 
   if (waitfdtimed(fd, timedone) == -1)
      return (ssize_t)(-1);
   return r_read(fd, buf, nbyte);
}
