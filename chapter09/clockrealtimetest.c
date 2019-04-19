#include <stdio.h>
#include <time.h>
#define BILLION 1000000000L
#define NUMDIF 20

int main(void) {
   int i;
   int numcalls = 1;
   int numdone = 0;
   long sum = 0;
   long timedif[NUMDIF];
   struct timespec tlast;
   struct timespec tthis;

   if (clock_getres(CLOCK_REALTIME, &tlast)) 
      perror("Failed to get clock resolution");
   else if (tlast.tv_sec != 0)
      printf("Clock resolution no better than one second\n");
   else 
      printf("Clock resolution: %ld nanoseconds\n", (long)tlast.tv_nsec);
   if (clock_gettime(CLOCK_REALTIME, &tlast)) {
      perror("Failed to get first time");
      return 1;
   }
   while (numdone < NUMDIF) {
      numcalls++;
      if (clock_gettime(CLOCK_REALTIME, &tthis)) {
         perror("Failed to get a later time");
         return 1;
      }
      timedif[numdone] =  BILLION*(tthis.tv_sec - tlast.tv_sec) +
                      tthis.tv_nsec - tlast.tv_nsec;
      if (timedif[numdone] != 0) {
         numdone++;
         tlast = tthis;
      }
   }
   printf("Found %d differences in CLOCK_REALTIME:\n", NUMDIF);
   printf("%d calls to CLOCK_REALTIME were required\n", numcalls);
   for (i = 0; i < NUMDIF; i++) {
      printf("%2d: %10ld nanoseconds\n", i, timedif[i]);
      sum += timedif[i];
   }
   printf("The average nonzero difference is %f\n", sum/(double)NUMDIF);
   return 0;
}
