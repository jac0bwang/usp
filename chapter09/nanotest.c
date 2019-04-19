#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#define COUNT 100
#define D_BILLION 1000000000.0
#define D_MILLION 1000000.0
#define MILLION 1000000L
#define NANOSECONDS 1000

int main(void) {
   int i;
   struct timespec slptm;
   long tdif;
   struct timeval tend, tstart;
 
   slptm.tv_sec = 0;
   slptm.tv_nsec = NANOSECONDS;
   if (gettimeofday(&tstart, NULL) == -1) {
      fprintf(stderr, "Failed to get start time\n");
      return 1;
   }
   for (i = 0; i < COUNT; i++)
      if (nanosleep(&slptm, NULL) == -1) {
         perror("Failed to nanosleep");
         return 1;
      }
   if (gettimeofday(&tend, NULL) == -1) {
      fprintf(stderr, "Failed to get end time\n");
      return 1;
   }
   tdif = MILLION*(tend.tv_sec - tstart.tv_sec) +
                   tend.tv_usec - tstart.tv_usec;
   printf("%d nanosleeps of %d nanoseconds\n", COUNT, NANOSECONDS);
   printf("Should take   %11d microseconds or %f seconds\n",
             NANOSECONDS*COUNT/1000, NANOSECONDS*COUNT/D_BILLION);
   printf("Actually took %11ld microseconds or %f seconds\n", tdif,
             tdif/D_MILLION);
   printf("Number of seconds per nanosleep was       %f\n",
             (tdif/(double)COUNT)/MILLION);
   printf("Number of seconds per nanosleep should be %f\n",
             NANOSECONDS/D_BILLION);
   return 0;
}
