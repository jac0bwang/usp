#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
   int signalcount = 0;
   int signo;
   int signum = SIGUSR1;
   sigset_t sigset;

   if ((sigemptyset(&sigset) == -1) ||
       (sigaddset(&sigset, signum) == -1) ||
       (sigprocmask(SIG_BLOCK, &sigset, NULL) == -1))
      perror("Failed to block signals before sigwait"); 
   fprintf(stderr, "This process has ID %ld\n", (long)getpid());
   for ( ; ; ) {
      if (sigwait(&sigset, &signo) == -1) {
         perror("Failed to wait using sigwait");
         return 1;
      }
      signalcount++;
      fprintf(stderr, "Number of signals so far: %d\n", signalcount);
   }
}
