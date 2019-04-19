#include <errno.h>
#include <pthread.h>

static pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;
static int limit = 0;

int initbarrier(int n) {              /* initialize the barrier to be size n */
   int error;

   if (error = pthread_mutex_lock(&bmutex))        /* couldn't lock, give up */
      return error;
   if (limit != 0) {                 /* barrier can only be initialized once */
      pthread_mutex_unlock(&bmutex);
      return EINVAL;
   }
   limit = n;
   return pthread_mutex_unlock(&bmutex);
}
   
int waitbarrier(void) {    /* wait at the barrier until all n threads arrive */
   int berror = 0;
   int error;

   if (error = pthread_mutex_lock(&bmutex))        /* couldn't lock, give up */
      return error;
   if (limit <=  0) {                       /* make sure barrier initialized */
      pthread_mutex_unlock(&bmutex);
      return EINVAL; 
   }
   count++;
   while ((count < limit) && !berror)
      berror =  pthread_cond_wait(&bcond, &bmutex); 
   if (!berror)  
      berror = pthread_cond_broadcast(&bcond);           /* wake up everyone */
   error = pthread_mutex_unlock(&bmutex);
   if (berror)
      return berror;
   return error;
} 
