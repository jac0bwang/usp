#include <pthread.h>
#include "buffer.h"
static buffer_t buffer[BUFSIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;
static int bufin = 0;
static int bufout = 0;
static pthread_cond_t items = PTHREAD_COND_INITIALIZER;
static pthread_cond_t slots = PTHREAD_COND_INITIALIZER;
static int totalitems = 0;

int getitem(buffer_t *itemp) { /* remove an item from buffer and put in itemp */
   int error;
   if (error = pthread_mutex_lock(&bufferlock)) 
      return error;
   while ((totalitems <= 0) && !error)
      error = pthread_cond_wait (&items, &bufferlock);
   if (error) {
      pthread_mutex_unlock(&bufferlock);
      return error;
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

int putitem(buffer_t item) {                  /* insert an item in the buffer */
   int error;
   if (error = pthread_mutex_lock(&bufferlock))
      return error;
   while ((totalitems >= BUFSIZE) && !error)
      error = pthread_cond_wait (&slots, &bufferlock);
   if (error) {
      pthread_mutex_unlock(&bufferlock);
      return error;
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
