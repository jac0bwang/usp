#include <pthread.h> 
#include <stdio.h>
#include <string.h> 
#define NUMTHREADS 10

int initshared(int val);
int incshared();
int getshared(int *sval);

/* ARGSUSED */
static void *increment(void *args) {
   int i;
   for (i=0;i<100;i++)
      incshared();
   return NULL;
}
 
int main (void) {
   int error;
   int i;
   pthread_t tid[NUMTHREADS];
   int val;

   if (initshared(0)) {
      perror("Could not initialize shared variable");
      return 1;
   }
   getshared(&val);
   printf("Shared variable initialized to %d\n", val);

   for (i = 0; i < NUMTHREADS; i++) 
      if (error = pthread_create(tid+i, NULL, increment, NULL))
         fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
   printf("Number of threads created: %d\n", NUMTHREADS);
   for (i = 0; i < NUMTHREADS; i++)
      if (error = pthread_join(tid[i], NULL))
         fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
   printf("All threads done\n");
   getshared(&val);
   printf("Shared variable now has value %d\n", val);
   return 0;
}

