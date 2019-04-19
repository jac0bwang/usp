#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int initsuspend(int signo);
int restore(void);
int simplesuspend(void);

int main(void) {
   fprintf(stderr, "This is process %ld\n", (long)getpid());
   for ( ; ; ) {
      if (initsuspend(SIGUSR1)) {
         perror("Failed to setup handler for SIGUSR1");
         return 1;
      }
      fprintf(stderr, "Waiting for signal\n");
      if (simplesuspend()) {
         perror("Failed to suspend for signal");
         return 1;
      }
      fprintf(stderr, "Got signal\n");
      if (restore()) {
         perror("Failed to restore original handler");
         return 1;
      }
   }
   return 1;
}
