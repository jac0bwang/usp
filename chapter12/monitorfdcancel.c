#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void *processfdcancel(void *arg);

void monitorfdcancel(int fd[], int numfds) {
   int error;
   int i;
   pthread_t *tid;
    
   if ((tid = (pthread_t *)calloc(numfds, sizeof(pthread_t))) == NULL) {
      perror("Unable to allocate space for thread IDs");
      return;
   }
                         /* create a thread for each file descriptor */
   for (i = 0; i < numfds; i++)
      if (error = pthread_create((tid + i), NULL, processfdcancel, (fd + i)))
         fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(error));
   for (i = 0; i < numfds; i++)
      if (error = pthread_join(*(tid + i), NULL))
         fprintf(stderr, "Error joining thread %d: %s\n", i, strerror(error));
   free(tid);
   return;
}
