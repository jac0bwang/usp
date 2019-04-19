#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include "restart.h"
#define MILLION 1000000.0

/* return -1 if timeout time has passed, 0 otherwise */
static int fixtimeout(struct timeval *startp, struct timeval *timeoutp) {
   struct timeval now;

   gettimeofday(&now, NULL);
   timeoutp->tv_sec = startp->tv_sec - now.tv_sec + timeoutp->tv_sec;
   timeoutp->tv_usec = startp->tv_usec - now.tv_usec + timeoutp->tv_usec;
   if (timeoutp->tv_usec >= MILLION) {
      timeoutp->tv_sec++;
      timeoutp->tv_usec -= MILLION;
   } 
   if (timeoutp->tv_usec < 0) {
      timeoutp->tv_sec--;
      timeoutp->tv_usec += MILLION;
   } 
   if ( (timeoutp->tv_sec < 0) ||
       ((timeoutp->tv_sec == 0) && (timeoutp->tv_usec == 0)))
      return -1;
   return 0;
}

ssize_t readtimed(int fd, void *buf, size_t nbyte, double seconds) {
   int nfds;
   fd_set readset;
   int retval;
   struct timeval start, timeout, timeoutsave;

   if ((fd < 0) || (fd >= FD_SETSIZE)) {
      errno = EINVAL;
      return -1;
   }
   if (seconds > 0) {
      nfds = fd + 1;
      FD_ZERO(&readset);
      FD_SET(fd, &readset);
      gettimeofday(&start, NULL);
      timeoutsave.tv_sec = (int)seconds;
      timeoutsave.tv_usec =
         (int)((seconds - timeoutsave.tv_sec)*MILLION + 0.5);
      if (timeoutsave.tv_usec >= MILLION) {
         timeoutsave.tv_sec++;
         timeoutsave.tv_usec -= MILLION;
      } 
      timeout = timeoutsave;

      while ( ((retval = select(nfds, &readset, NULL, NULL, &timeout)) == -1)
              && (errno == EINTR) ) {
         timeout = timeoutsave;
         if (fixtimeout(&start, &timeout) == -1) {
            errno = ETIME;
            return (ssize_t)(-1);
         }  
         FD_ZERO(&readset);
         FD_SET(fd, &readset);
      }
      if (retval == -1)   /* select had an error */
         return (ssize_t)(-1);
      if (retval == 0) {  /* select timed out */
         errno = ETIME;
         return (ssize_t)(-1);
      }  
   }   
   return r_read(fd, buf, nbyte);
}
