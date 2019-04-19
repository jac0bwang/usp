#include <pthread.h>

int testandsetonce(int *ovalue) {
   static int done = 0; 
   static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
   int error;   
   if (error = pthread_mutex_lock(&lock))
      return error; 
   *ovalue = done;
   done = 1; 
   return pthread_mutex_unlock(&lock);
}
