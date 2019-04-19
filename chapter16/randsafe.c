#include <pthread.h>
#include <stdlib.h>

int randsafe(double *ranp) {
   static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
   int error;   

   if (error = pthread_mutex_lock(&lock))
      return error; 
   *ranp = (rand() + 0.5)/(RAND_MAX + 1.0);
   return pthread_mutex_unlock(&lock);
}
