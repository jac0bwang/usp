#include <pthread.h>
#include <stdio.h>

void *detachfun(void *arg) {
   int i = *((int *)(arg));
   if (!pthread_detach(pthread_self())) 
      return NULL;
   fprintf(stderr, "My argument is %d\n", i);
   return NULL;
}
