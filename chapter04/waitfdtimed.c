#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include "restart.h"
#define MILLION 1000000L
#define D_MILLION 1000000.0

static int gettimeout(struct timeval end,
                               struct timeval *timeoutp) {
   gettimeofday(timeoutp, NULL);
   timeoutp->tv_sec = end.tv_sec - timeoutp->tv_sec;
   timeoutp->tv_usec = end.tv_usec - timeoutp->tv_usec;
   if (timeoutp->tv_usec >= MILLION) {
      timeoutp->tv_sec++;
      timeoutp->tv_usec -= MILLION;
   } 
   if (timeoutp->tv_usec < 0) {
      timeoutp->tv_sec--;
      timeoutp->tv_usec += MILLION;
   } 
   if ((timeoutp->tv_sec < 0) ||
       ((timeoutp->tv_sec == 0) && (timeoutp->tv_usec == 0))) {
      errno = ETIME;
      return -1;
   }
   return 0;
}

struct timeval add2currenttime(double seconds) {
   struct timeval newtime;

   gettimeofday(&newtime, NULL);
   newtime.tv_sec += (int)seconds;
   newtime.tv_usec += (int)((seconds - (int)seconds)*D_MILLION + 0.5);
   if (newtime.tv_usec >= MILLION) {
      newtime.tv_sec++;
      newtime.tv_usec -= MILLION;
   } 
   return newtime;
}

int waitfdtimed(int fd, struct timeval end) {
   fd_set readset;
   int retval;
   struct timeval timeout;

   if ((fd < 0) || (fd >= FD_SETSIZE)) {
      errno = EINVAL;
      return -1;
   }  
   FD_ZERO(&readset);
   FD_SET(fd, &readset);
   if (gettimeout(end, &timeout) == -1)
      return -1;
   while (((retval = select(fd + 1, &readset, NULL, NULL, &timeout)) == -1)
           && (errno == EINTR)) {
      if (gettimeout(end, &timeout) == -1)
         return -1;
      FD_ZERO(&readset);
      FD_SET(fd, &readset);
   }
   if (retval == 0) {
      errno = ETIME;
      return -1;
   }
   if (retval == -1)
      return -1;
   return 0;
}
