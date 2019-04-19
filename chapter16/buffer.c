#include <errno.h>
#include <pthread.h>
#include "buffer.h"
static buffer_t buffer[BUFSIZE];
static pthread_mutex_t  bufferlock = PTHREAD_MUTEX_INITIALIZER;
static int bufin = 0;
static int bufout = 0;
static int totalitems = 0;

int getitem(buffer_t *itemp) {  /* remove item from buffer and put in *itemp */ 
   int error;
   int erroritem = 0;
   if (error = pthread_mutex_lock(&bufferlock))         /* no mutex, give up */
      return error; 
   if (totalitems > 0) {                   /* buffer has something to remove */
      *itemp = buffer[bufout];
       bufout = (bufout + 1) % BUFSIZE;
       totalitems--;
   } else
       erroritem = EAGAIN; 
   if (error = pthread_mutex_unlock(&bufferlock))  
      return error;                /* unlock error more serious than no item */
   return erroritem;
}

int putitem(buffer_t item) {                    /* insert item in the buffer */
   int error;
   int erroritem = 0; 
   if (error = pthread_mutex_lock(&bufferlock))         /* no mutex, give up */
      return error;
   if (totalitems < BUFSIZE) {           /* buffer has room for another item */
      buffer[bufin] = item;
      bufin = (bufin + 1) % BUFSIZE;
      totalitems++;
   } else
      erroritem = EAGAIN;
   if (error = pthread_mutex_unlock(&bufferlock))
      return error;                /* unlock error more serious than no slot */
   return erroritem; 
}
