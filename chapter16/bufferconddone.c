#include <errno.h>
#include <pthread.h>
#include "buffer.h"
static buffer_t buffer[BUFSIZE];
static pthread_mutex_t  bufferlock = PTHREAD_MUTEX_INITIALIZER;
static int bufin = 0;
static int bufout = 0;
static int doneflag = 0;
static pthread_cond_t items = PTHREAD_COND_INITIALIZER;
static pthread_cond_t slots = PTHREAD_COND_INITIALIZER;
static int totalitems = 0;

int getitem(buffer_t *itemp) {/* remove an item from buffer and put in itemp */
   int error;
   if (error = pthread_mutex_lock(&bufferlock)) 
      return error;
   while ((totalitems <= 0) && !error && !doneflag)
      error = pthread_cond_wait (&items, &bufferlock);
   if (error) {
      pthread_mutex_unlock(&bufferlock);
      return error;
   }
   if (doneflag && (totalitems <= 0)) {
      pthread_mutex_unlock(&bufferlock); 
      return ECANCELED;
   } 
   *itemp = buffer[bufout];
   bufout = (bufout + 1) % BUFSIZE;
   totalitems--;
   if (error = pthread_cond_signal(&slots)) {
      pthread_mutex_unlock(&bufferlock);
      return error;
   }
   return pthread_mutex_unlock(&bufferlock);
}

int putitem(buffer_t item) {                 /* insert an item in the buffer */
   int error;
   if (error = pthread_mutex_lock(&bufferlock))
      return error;
   while ((totalitems >= BUFSIZE) && !error && !doneflag)
      error = pthread_cond_wait (&slots, &bufferlock);
   if (error) {
      pthread_mutex_unlock(&bufferlock);
      return error;
   }  
   if (doneflag) {               /* consumers may be gone, don't put item in */
      pthread_mutex_unlock(&bufferlock); 
      return ECANCELED; 
   } 
   buffer[bufin] = item;
   bufin = (bufin + 1) % BUFSIZE;
   totalitems++;
   if (error = pthread_cond_signal(&items)) {
      pthread_mutex_unlock(&bufferlock); 
      return error; 
   } 
   return pthread_mutex_unlock(&bufferlock);
}

int getdone(int *flag) {                                     /* get the flag */
   int error;
   if (error = pthread_mutex_lock(&bufferlock))
      return error;
   *flag = doneflag;
   return pthread_mutex_unlock(&bufferlock);
}

int setdone(void) {       /* set the doneflag and inform all waiting threads */
   int error1;
   int error2;
   int error3;
 
   if (error1 = pthread_mutex_lock(&bufferlock))
      return error1;
   doneflag = 1;
   error1 = pthread_cond_broadcast(&items);              /* wake up everyone */
   error2 = pthread_cond_broadcast(&slots);
   error3 = pthread_mutex_unlock(&bufferlock);
   if (error1)
      return error1;
   if (error2)
      return error2;
   if (error3)
      return error3;
   return 0;
}
