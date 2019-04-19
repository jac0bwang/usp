#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *threadout(void *args);

int main(int argc, char *argv[]) {
   int error;
   int i;
   int n;
   pthread_t *tids;

   if (argc != 2){   /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s numthreads\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   tids = (pthread_t *)calloc(n, sizeof(pthread_t));
   if (tids == NULL) {
      perror("Failed to allocate memory for thread IDs");
      return 1;
   }
   for (i = 0; i < n; i++)
      if (error = pthread_create(tids+i, NULL, threadout, NULL)) {
         fprintf(stderr, "Failed to create thread:%s\n", strerror(error));
         return 1;
      }
   for (i = 0; i < n; i++)
      if (error = pthread_join(tids[i], NULL)) {
         fprintf(stderr, "Failed to join thread:%s\n", strerror(error));
         return 1;
      }
   return 0;
}
