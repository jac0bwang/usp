#include <pthread.h>
static int count = 0; 
static pthread_mutex_t  countlock = PTHREAD_MUTEX_INITIALIZER;

int increment(void) {                  /* increment the counter */
   int error;   
   if (error = pthread_mutex_lock(&countlock))
      return error; 
   count++;
   return pthread_mutex_unlock(&countlock);
}

int decrement(void) {                 /* decrement the counter */
   int error;
   if (error = pthread_mutex_lock(&countlock))
      return error;
   count--; 
   return pthread_mutex_unlock(&countlock);
}

int getcount(int *countp) {           /* retrieve the counter */
   int error; 
   if (error = pthread_mutex_lock(&countlock)) 
      return error; 
   *countp = count;  
   return pthread_mutex_unlock(&countlock); 
} 
