#include <pthread.h>
static int seminit = 0;
static pthread_mutex_t smutex = PTHREAD_MUTEX_INITIALIZER;

int bufferinit(void);

int bufferinitmutex(void) {                /* initialize buffer at most once */ 
   int error = 0;
   int errorinit = 0;
   if (error = pthread_mutex_lock(&smutex))
       return error;
   if (!seminit && !(errorinit = bufferinit()))
       seminit = 1;
   error = pthread_mutex_unlock(&smutex); 
   if (errorinit)              /* buffer initialization error occurred first */ 
      return errorinit;
   return error; 
}
