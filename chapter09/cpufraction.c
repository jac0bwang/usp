#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

void function_to_time(void);

int main(void) { 
   double clockticks, cticks;
   clock_t tcend, tcstart;
   struct tms tmend, tmstart;

   if ((clockticks = (double) sysconf(_SC_CLK_TCK)) == -1) {
      perror("Failed to determine clock ticks per second");
      return 1;
   }
   printf("The number of ticks per second is %f\n", clockticks);
   if (clockticks == 0) {
      fprintf(stderr, "The number of ticks per second is invalid\n");
      return 1;
   }
   if ((tcstart = times(&tmstart)) == -1) {
      perror("Failed to get start time");
      return 1;
   }
   function_to_time(); 
   if ((tcend = times(&tmend)) == -1) {
      perror("Failed to get end times");
      return 1;
   }
   cticks = tmend.tms_utime + tmend.tms_stime 
             - tmstart.tms_utime - tmstart.tms_stime;
   printf("Total CPU time for operation is %f seconds\n", cticks/clockticks); 
   if ((tcend <= tcstart) || (tcend < 0) || (tcstart < 0)) {
      fprintf(stderr, "Tick time wrapped, couldn't calculate fraction\n");
      return 1;
   }
   printf("Fraction of CPU time used is %f\n", cticks/(tcend - tcstart));
   return 0;
} 
