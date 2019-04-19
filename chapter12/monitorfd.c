#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *processfd(void *arg);

void monitorfd(int fd[], int numfds) {       /* create threads to monitor fds */
   int error, i;
   pthread_t *tid;
    
   if ((tid = (pthread_t *)calloc(numfds, sizeof(pthread_t))) == NULL) {
      perror("Failed to allocate space for thread IDs");
      return;
   }
   for (i = 0; i < numfds; i++)   /* create a thread for each file descriptor */
      if (error = pthread_create(tid + i, NULL, processfd, (fd + i))) {
         fprintf(stderr, "Failed to create thread %d: %s\n",
                         i, strerror(error));
         tid[i] = pthread_self();
      }
   for (i = 0; i < numfds; i++) {
      if (pthread_equal(pthread_self(), tid[i]))
         continue;
      if (error = pthread_join(tid[i], NULL))
         fprintf(stderr, "Failed to join thread %d: %s\n", i, strerror(error));
   }
   free(tid);
   return;
}
