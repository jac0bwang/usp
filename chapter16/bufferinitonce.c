#include <pthread.h>
static int initerror = 0; 
static pthread_once_t initonce = PTHREAD_ONCE_INIT; 

int bufferinit(void);

static void initialization(void) {
   initerror = bufferinit();
   return;
}
 
int bufferinitonce(void) {                 /* initialize buffer at most once */
   int error;
   if (error = pthread_once(&initonce, initialization))
      return error;
   return initerror;
}
