#include <math.h>
#include <pthread.h>
#include "buffer.h"
#include "globalerror.h"
#include "sharedsum.h"

/* ARGSUSED */
static void *consumer(void *arg) {                   /* compute partial sums */ 
   int error;
   buffer_t nextitem;
   double value;
 
   for (  ;  ;  )  {
      if (error = getitem(&nextitem))              /* retrieve the next item */
         break;
      value = sin(nextitem);
      if (error = add(value))
         break;
   }
   seterror(error);
   return NULL;
}

/* --------------- Public functions ---------------------------------------- */
int initconsumer(pthread_t *tconsumer) {                       /* initialize */
   int error;

   error = pthread_create(tconsumer, NULL, consumer, NULL);
   return (seterror(error));
}
