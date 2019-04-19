#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "hardwaretimer.h"

static int timerexpired = 0;

static void myalarm() {
   timerexpired = 1;
}

int main(int argc, char *argv[]) {   /* Test the hardware timer and prototype */
   long interval;
   int n1;
   int n2;

   if (argc != 1) {
      fprintf(stderr, "Usage: %s\n", argv[0]);
      return 1;
   }
   catchsetup(myalarm);

   for( ; ; ){
      if (scanf("%ld%d%d%*[^\n]", &interval, &n1, &n2) == EOF)
         break;
      if (interval <= 0)
         break;
      blockinterrupt();
      sethardwaretimer(interval);
      while (!timerexpired)
         waitforinterrupt();
      timerexpired = 0;
      if (n1 < 0)
         break;
      printf("%d %d\n", n1, n2);
      fflush(stdout);
      fprintf(stderr, "%d %d\n", n1, n2);
   }
   return 0;
}
