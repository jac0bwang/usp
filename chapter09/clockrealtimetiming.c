#include <stdio.h>
#include <time.h>
#define MILLION 1000000L

void function_to_time(void);
 
int main (void) {
   long timedif;
   struct timespec tpend, tpstart;
 
   if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) {
      perror("Failed to get starting time");
      return 1;
   }
   function_to_time();                           /* timed code goes here */
   if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
      perror("Failed to get ending time");
      return 1;
   }
   timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
            (tpend.tv_nsec - tpstart.tv_nsec)/1000;
   printf("The function_to_time took %ld microseconds\n", timedif);
   return 0;
}
