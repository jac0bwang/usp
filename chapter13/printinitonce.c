#include <pthread.h>
#include <stdio.h>

static pthread_once_t initonce = PTHREAD_ONCE_INIT; 
int var;

static void initialization(void) {
   var = 1; 
   printf("The variable was initialized to %d\n", var); 
}
 
int printinitonce(void) {        /* call initialization at most once */
   return pthread_once(&initonce, initialization);
}

