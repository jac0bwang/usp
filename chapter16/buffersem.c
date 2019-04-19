#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include "buffer.h"
static buffer_t buffer[BUFSIZE];
static pthread_mutex_t  bufferlock = PTHREAD_MUTEX_INITIALIZER;
static int bufin = 0;
static int bufout = 0;
static volatile sig_atomic_t initdone = 0;
static int initerror = 0;
static pthread_once_t initonce = PTHREAD_ONCE_INIT;
static sem_t semitems;
static sem_t semslots;

static int bufferinit(void) { /* called exactly once by getitem and putitem  */
   int error;
   if (sem_init(&semitems, 0, 0))
      return errno;
   if (sem_init(&semslots, 0, BUFSIZE)) {
      error = errno;
      sem_destroy(&semitems);                    /* free the other semaphore */
      return error;
   }
   return 0;
}

static void initialization(void) {
   initerror = bufferinit();
   if (!initerror)
      initdone = 1;
}

static int bufferinitonce(void) {          /* initialize buffer at most once */
   int error;
   if (error = pthread_once(&initonce, initialization))
      return error;
   return initerror;
}

int getitem(buffer_t *itemp) {  /* remove item from buffer and put in *itemp */
   int error;
   if (!initdone)
      bufferinitonce();
   while (((error = sem_wait(&semitems)) == -1) && (errno == EINTR)) ;
   if (error)
      return errno;
   if (error = pthread_mutex_lock(&bufferlock))
      return error; 
   *itemp = buffer[bufout];
   bufout = (bufout + 1) % BUFSIZE;
   if (error = pthread_mutex_unlock(&bufferlock))
      return error;
   if (sem_post(&semslots) == -1)  
      return errno; 
   return 0; 
}

int putitem(buffer_t item) {                    /* insert item in the buffer */
   int error;
   if (!initdone)
      bufferinitonce();
   while (((error = sem_wait(&semslots)) == -1) && (errno == EINTR)) ;
   if (error)
      return errno;
   if (error = pthread_mutex_lock(&bufferlock))
      return error;    
   buffer[bufin] = item;
   bufin = (bufin + 1) % BUFSIZE;
   if (error = pthread_mutex_unlock(&bufferlock))
      return error; 
   if (sem_post(&semitems) == -1)  
      return errno; 
   return 0; 
}
