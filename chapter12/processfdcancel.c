#include <pthread.h>
#include "restart.h"
#define BUFSIZE 1024

void docommand(char *cmd, int cmdsize);

void *processfdcancel(void *arg) { /* process commands with cancellation */
   char buf[BUFSIZE];
   int fd;
   ssize_t nbytes;
   int newstate, oldstate;

   fd = *((int *)(arg));
   for ( ; ; )  {
      if ((nbytes = r_read(fd, buf, BUFSIZE)) <= 0) 
         break;
      if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate))
         return arg;
      docommand(buf, nbytes);
      if (pthread_setcancelstate(oldstate, &newstate))
         return arg;
   }
   return NULL;
}
