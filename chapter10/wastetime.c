#include <stdio.h>
#include <sys/time.h>
#define MILLION 1000000L

int wastetime(int maxus) {               /* waste maxus microseconds of time */
   long timedif;
   struct timeval tp1, tp2;

   if (gettimeofday(&tp1, NULL)) {
      fprintf(stderr, "Failed to get initial time\n");
      return 1;
   }
   timedif = 0;
   while (timedif < maxus) {
      if (gettimeofday(&tp2, NULL)) {
         fprintf(stderr, "Failed to get check time\n");
         return 1;
      }
      timedif = MILLION*(tp2.tv_sec - tp1.tv_sec) +
                   tp2.tv_usec - tp1.tv_usec;
      if (timedif < 0)
         break;
   }
   return 0;
}
