#include <pthread.h>
static int doneflag = 0; 
static pthread_mutex_t donelock = PTHREAD_MUTEX_INITIALIZER;

int getdone(int *flag) {                   /* get the flag */
   int error;   
   if (error = pthread_mutex_lock(&donelock))
      return error; 
   *flag = doneflag;
   return pthread_mutex_unlock(&donelock);
}

int setdone(void) {                        /* set the flag */
   int error;
   if (error = pthread_mutex_lock(&donelock))
      return error; 
   doneflag = 1; 
   return pthread_mutex_unlock(&donelock);
}
