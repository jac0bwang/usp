#include <stdio.h>
#include <sys/time.h>
#define MILLION 1000000L
#define NUMDIF 20

int main(void) {
   int i;
   int numcalls = 1;
   int numdone = 0;
   long sum = 0;
   long timedif[NUMDIF];
   struct timeval tlast;
   struct timeval tthis;

   if (gettimeofday(&tlast, NULL)) {
      fprintf(stderr, "Failed to get first gettimeofday.\n");
      return 1;
   }
   while (numdone < NUMDIF) {
      numcalls++;
      if (gettimeofday(&tthis, NULL)) {
         fprintf(stderr, "Failed to get a later gettimeofday.\n");
         return 1;
      }
      timedif[numdone] =  MILLION*(tthis.tv_sec - tlast.tv_sec) +
                      tthis.tv_usec - tlast.tv_usec;
      if (timedif[numdone] != 0) {
         numdone++;
         tlast = tthis;
      }
   }
   printf("Found %d differences in gettimeofday:\n", NUMDIF);
   printf("%d calls to gettimeofday were required\n", numcalls);
   for (i = 0; i < NUMDIF; i++) {
      printf("%2d: %10ld microseconds\n", i, timedif[i]);
      sum += timedif[i];
   }
   printf("The average nonzero difference is %f\n", sum/(double)NUMDIF);
   return 0;
}
