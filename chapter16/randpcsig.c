#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "buffer.h"
#include "globalerror.h"
#include "sharedsum.h"
#include "signalthread.h"

int initconsumer(pthread_t *tid);
int initproducer(pthread_t *tid);
int showresults(void);

int main(int argc, char *argv[]) {
   int error;
   int i;
   int numberconsumers;
   int numberproducers;
   pthread_t *tidc;
   pthread_t *tidp;

   if (argc != 3) {  
      fprintf(stderr, "Usage: %s producers consumers\n", argv[0]);
      return 1;
   }
   numberproducers = atoi(argv[1]);
   numberconsumers = atoi(argv[2]);
   if (error = signalthreadinit(SIGUSR1)) {
      perror("Failed to start signalthread");
      return 1;
   }
   fprintf(stderr,"Process %ld will run until SIGUSR1 (%d) signal.\n",
                   (long)getpid(), SIGUSR1);
   tidp = (pthread_t *)calloc(numberproducers, sizeof(pthread_t));
   if (tidp == NULL) {
      perror("malloc producer IDs");
      return 1;
   }
   tidc = (pthread_t *)calloc(numberconsumers, sizeof(pthread_t));
   if (tidc == NULL) {
      perror("malloc consumer IDs");
      return 1;
   }
   for (i = 0; i < numberconsumers; i++)             /* initialize consumers */
      if (error = initconsumer(tidc + i)) {
         fprintf(stderr, "Failed to create consumer %d:%s\n",
                          i, strerror(error));
         return 1;
      }
   for (i = 0; i < numberproducers; i++)             /* initialize producers */
      if (error = initproducer(tidp + i)) {
         fprintf(stderr, "Failed to create producer %d:%s\n",
                          i, strerror(error));
         return 1;
      }
   for (i = 0; i < numberproducers; i++)               /* wait for producers */
      if (error = pthread_join(tidp[i], NULL)) {
         fprintf(stderr, "Failed producer %d join:%s\n", i, strerror(error));
         return 1;
      }  
   for (i = 0; i < numberconsumers; i++)               /* wait for consumers */
      if (error = pthread_join(tidc[i], NULL)) {
         fprintf(stderr, "Failed consumer %d join:%s\n", i, strerror(error));
         return 1;
      }  
   if (showresults())
      return 1;
   return 0;
}
