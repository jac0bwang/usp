#include <pthread.h>
#include "globalerror.h"

static int count = 0;
static double sum = 0.0; 
static pthread_mutex_t  sumlock = PTHREAD_MUTEX_INITIALIZER;

int add(double x) {                                          /* add x to sum */
   int error;
   if (error = pthread_mutex_lock(&sumlock))
      return seterror(error);
   sum += x;
   count++;
   error = pthread_mutex_unlock(&sumlock);
   return seterror(error);
}

int getsum(double *sump) {                                     /* return sum */
   int error;   
   if (error = pthread_mutex_lock(&sumlock))
      return seterror(error);
   *sump = sum;
   error = pthread_mutex_unlock(&sumlock);
   return seterror(error);
}

int getcountandsum(int *countp, double *sump) {      /* return count and sum */
   int error;   
   if (error = pthread_mutex_lock(&sumlock))
      return seterror(error);
   *countp = count;
   *sump = sum;
   error = pthread_mutex_unlock(&sumlock);
   return seterror(error);
}
