#include <pthread.h> 
#include <stdio.h>
#include <string.h> 
#define NUMTHREADS 10

static void *printarg(void *arg) { 
   fprintf(stderr, "Thread received %d\n", *(int *)arg);
   return NULL;
}
 
int main (void) {        /* program incorrectly passes parameters to threads */
   int error;
   int i;
   int j;
   pthread_t tid[NUMTHREADS];
   
   for (i = 0; i < NUMTHREADS; i++) 
      if (error = pthread_create(tid + i, NULL, printarg, (void *)&i)) {
         fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
         tid[i] = pthread_self();
      }
   for (j = 0; j < NUMTHREADS; j++) {
      if (pthread_equal(pthread_self(), tid[j]))
         continue;
      if (error = pthread_join(tid[j], NULL))
         fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
   }
   printf("All threads done\n");
   return 0;
}
