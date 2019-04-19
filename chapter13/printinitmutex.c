#include <pthread.h>
#include <stdio.h>

int printinitmutex(int *var, int value) {
   static int done = 0; 
   static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
   int error;   
   if (error = pthread_mutex_lock(&lock))
      return error; 
   if (!done) {
      *var = value;
      printf("The variable was initialized to %d\n", value);
      done = 1;
   }
   return pthread_mutex_unlock(&lock);
}
