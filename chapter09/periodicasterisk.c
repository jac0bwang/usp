#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/time.h>

/* ARGSUSED */
static void myhandler(int s) {
   char aster = '*';
   int errsave;
   errsave = errno;
   write(STDERR_FILENO, &aster, 1);
   errno = errsave;
}

static int setupinterrupt(void) {          /* set up myhandler for  SIGPROF */
   struct sigaction act;
   act.sa_handler = myhandler;
   act.sa_flags = 0;
   return (sigemptyset(&act.sa_mask) || sigaction(SIGPROF, &act, NULL));
}

static int setupitimer(void) {    /* set ITIMER_PROF for 2-second intervals */
   struct itimerval value;
   value.it_interval.tv_sec = 2;
   value.it_interval.tv_usec = 0;
   value.it_value = value.it_interval;
   return (setitimer(ITIMER_PROF, &value, NULL));
}
 
int main(void) {
   if (setupinterrupt()) {
      perror("Failed to set up handler for SIGPROF");
      return 1;
   }
   if (setupitimer() == -1) {
      perror("Failed to set up the ITIMER_PROF interval timer"); 
      return 1;
   }
   for ( ; ; );                        /* execute rest of main program here */
}
