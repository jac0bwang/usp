#include <pthread.h>
#include "buffer.h"
static buffer_t buffer[BUFSIZE];
static pthread_mutex_t  bufferlock = PTHREAD_MUTEX_INITIALIZER;
static int bufin = 0;
static int bufout = 0;

int getitem(buffer_t *itemp) {  /* remove item from buffer and put in *itemp */
   int error;
   if (error = pthread_mutex_lock(&bufferlock))         /* no mutex, give up */
      return error; 
   *itemp = buffer[bufout];
   bufout = (bufout + 1) % BUFSIZE;
   return pthread_mutex_unlock(&bufferlock);
}

int putitem(buffer_t item) {                    /* insert item in the buffer */
   int error;
   if (error = pthread_mutex_lock(&bufferlock))         /* no mutex, give up */
      return error;
   buffer[bufin] = item;
   bufin = (bufin + 1) % BUFSIZE;
   return pthread_mutex_unlock(&bufferlock);
}
