#include <pthread.h>
static int globalerror = 0; 
static pthread_mutex_t errorlock = PTHREAD_MUTEX_INITIALIZER;

int geterror(int *error) {                             /* get the error flag */
   int terror;   
   if (terror = pthread_mutex_lock(&errorlock))
      return terror; 
   *error = globalerror;
   return pthread_mutex_unlock(&errorlock);
}

int seterror(int error) {         /* globalerror set to error if first error */
   int terror;
   if (!error)            /* it wasn't an error, so don't change globalerror */
      return error;
   if (terror = pthread_mutex_lock(&errorlock))         /* couldn't get lock */
      return terror;   
   if (!globalerror)
      globalerror = error; 
   terror = pthread_mutex_unlock(&errorlock);
   return terror? terror: error;
}
