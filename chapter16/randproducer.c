#include <pthread.h>
#include "buffer.h"
#include "globalerror.h"
#include "randsafe.h"

/* ARGSUSED */
static void *producer(void *arg1) {        /* generate pseudorandom numbers */
   int error;
   buffer_t item;

   for (  ;  ;  ) {
      if (error = randsafe(&item))
         break;
      if (error = putitem(item)) 
         break;
   }
   seterror(error);
   return NULL;
}

/* --------------- Public functions ---------------------------------------- */ 
int initproducer(pthread_t *tproducer) {                       /* initialize */ 
   int error;

   error = pthread_create(tproducer, NULL, producer, NULL);
   return (seterror(error)); 
}
