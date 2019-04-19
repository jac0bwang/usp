#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "computethread.h"
#include "globalerror.h"
#include "sharedsum.h"
#include "signalthread.h"

int showresults(void);
 
int main(int argc, char *argv[]) {
   int error;
   int i;
   int numthreads;
   pthread_t *tids; 

   if (argc != 2) {                   /* pass number threads on command line */
      fprintf(stderr, "Usage: %s numthreads\n", argv[0]);
      return 1;
   }
   if (error = signalthreadinit(SIGUSR1)) {          /* set up signal thread */
      fprintf(stderr, "Failed to set up signal thread: %s\n", strerror(error));
      return 1;
   }
   numthreads = atoi(argv[1]);
   if ((tids = (pthread_t *)calloc(numthreads, sizeof(pthread_t))) == NULL) {
      perror("Failed to allocate space for thread IDs"); 
      return 1;
   }
   for (i = 0; i < numthreads; i++)      /* create numthreads computethreads */
      if (error =  pthread_create(tids+ i, NULL, computethread, NULL)) { 
         fprintf(stderr, "Failed to start thread %d: %s\n", i,
                 strerror(error)); 
         return 1;
      }
   fprintf(stderr, "Send SIGUSR1(%d) signal to proc %ld to stop calculation\n",
                   SIGUSR1, (long)getpid());
   for (i = 0; i < numthreads; i++)    /* wait for computethreads to be done */
      if (error = pthread_join(tids[i], NULL)) {
         fprintf(stderr, "Failed to join thread %d: %s\n", i, strerror(error));
         return 1;
      }
   if (showresults())
      return 1;
   return 0;
}
