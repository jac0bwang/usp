#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 100

static char buf[BUFSIZE];
static int buflen = 0;

/* ARGSUSED */
static void handler(int signo) {          /* handler outputs result string */ 
   int savederrno;

   savederrno = errno;
   write(STDOUT_FILENO, buf, buflen);
   errno = savederrno;
}

static void results(int count, double sum) {       /* set up result string */
   double average;
   double calculated;
   double err;
   double errpercent;
   sigset_t oset;
   sigset_t sigset;

   if ((sigemptyset(&sigset) == -1) ||
        (sigaddset(&sigset, SIGUSR1) == -1) || 
        (sigprocmask(SIG_BLOCK, &sigset, &oset) == -1) )
      perror("Failed to block signal in results");
   if (count == 0)
      snprintf(buf, BUFSIZE, "No values calculated yet\n");
   else {
      calculated = 1.0 - cos(1.0);
      average = sum/count;
      err = average - calculated;
      errpercent = 100.0*err/calculated;
      snprintf(buf, BUFSIZE,
              "Count = %d, sum = %f, average = %f, error = %f or %f%%\n",
              count, sum, average, err, errpercent);
   }
   buflen = strlen(buf);
   if (sigprocmask(SIG_SETMASK, &oset, NULL) == -1)
      perror("Failed to unblock signal in results");
}

int main(void) {
   int count = 0;
   double sum = 0;
   double x;
   struct sigaction act;

   act.sa_handler = handler;
   act.sa_flags = 0;
   if ((sigemptyset(&act.sa_mask) == -1) || 
        (sigaction(SIGUSR1, &act, NULL) == -1) ) {
      perror("Failed to set SIGUSR1 signal handler");
      return 1;
   }
   fprintf(stderr, "Process %ld starting calculation\n", (long)getpid());
   for ( ; ; ) {
      if ((count % 10000) == 0)
         results(count, sum);
      x = (rand() + 0.5)/(RAND_MAX + 1.0);
      sum += sin(x);
      count++;
      if (count == INT_MAX)
         break;
   }
   results(count, sum);
   handler(0);        /* call handler directly to write out the results */
   return 0;
}
