#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "buffer.h"
#include "globalerror.h"
#include "sharedsum.h"

int initconsumer(pthread_t *tid);
int initproducer(pthread_t *tid);
int showresults(void);

int main(int argc, char *argv[]) {
   int error;
   int i;
   int numberconsumers;
   int numberproducers;
   int sleeptime;
   pthread_t tid;

   if (argc != 4) { 
      fprintf(stderr, "Usage: %s sleeptime producers consumers\n", argv[0]);
      return 1;
   }

   sleeptime = atoi(argv[1]);
   numberproducers = atoi(argv[2]);
   numberconsumers = atoi(argv[3]);
   for (i = 0; i < numberconsumers; i++)             /* initialize consumers */
      if (error = initconsumer(&tid)) {
         fprintf(stderr, "Failed to create consumer %d:%s\n",
                          i, strerror(error));
         return 1;
      }
   for (i = 0; i < numberproducers; i++)             /* initialize producers */
      if (error = initproducer(&tid)) {
         fprintf(stderr, "Failed to create producer %d:%s\n",
                          i, strerror(error));
         return 1;
      }

   sleep(sleeptime);                          /* wait to get the partial sum */
   if (showresults())
      return 1;
   sleep(sleeptime);                        /* wait again before terminating */
   if (showresults())
      return 1;
   return 0;
}
