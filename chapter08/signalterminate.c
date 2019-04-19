#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static volatile sig_atomic_t doneflag = 0;

/* ARGSUSED */
static void setdoneflag(int signo) {
   doneflag = 1;
}

int main (void) {
   struct sigaction act;
   int count = 0;
   double sum = 0;
   double x;

   act.sa_handler = setdoneflag;            /* set up signal handler */
   act.sa_flags = 0;
   if ((sigemptyset(&act.sa_mask) == -1) ||
       (sigaction(SIGINT, &act, NULL) == -1)) {
      perror("Failed to set SIGINT handler");
      return 1;
   }
    
   while (!doneflag) {
      x = (rand() + 0.5)/(RAND_MAX + 1.0);
      sum += sin(x);
      count++;
      printf("Count is %d and average is %f\n", count, sum/count);
   }

   printf("Program terminating ...\n");
   if (count == 0)
      printf("No values calculated yet\n");
   else
      printf("Count is %d and average is %f\n", count, sum/count);
   return 0;
}
