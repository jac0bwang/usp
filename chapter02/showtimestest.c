#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/wait.h>

int wastetime(int maxus);

static void showtimes(void) {
   double ticks;
   struct tms tinfo;

   if ((ticks = (double) sysconf(_SC_CLK_TCK)) == -1)
      perror("Failed to determine clock ticks per second");
   else if (times(&tinfo) == (clock_t)-1)
      perror("Failed to get times information");
   else {
      fprintf(stderr, "User time:              %8.3f seconds\n",
         tinfo.tms_utime/ticks);
      fprintf(stderr, "System time:            %8.3f seconds\n",
         tinfo.tms_stime/ticks);
      fprintf(stderr, "Children's user time:   %8.3f seconds\n",
         tinfo.tms_cutime/ticks);
      fprintf(stderr, "Children's system time: %8.3f seconds\n",
         tinfo.tms_cstime/ticks);
   }
}
 
int main(void) {
   if (atexit(showtimes))  {
      fprintf(stderr, "Failed to install showtimes exit handler\n");
      return 1; 
   }
   if (fork())
      wastetime(2900000);
   else
      wastetime(5400000);
   if (wait(NULL) > 0)
      fprintf(stderr, "\nChild has exited, parent stats follow:\n");
   return 0;
}
