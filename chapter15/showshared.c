#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getcountandsum(int *countp, double *sump);
int initshared(int key);

/* ARGSUSED */
static void showit(int signo) {
   int count;
   double sum;
   if (getcountandsum(&count, &sum) == -1)
      printf("Failed to get count and sum\n");
   else
      printf("Sum is %f and count is %d\n", sum, count);
}

int main(int argc, char *argv[]) {
   struct sigaction act;
   int key;
   sigset_t mask, oldmask;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s key\n", argv[0]);
      return 1;
   }
   key = atoi(argv[1]);
   if (initshared(key) == -1) {
      perror("Failed to initialize shared memory");
      return 1;
   }
   if ((sigfillset(&mask) == -1) || 
       (sigprocmask(SIG_SETMASK, &mask, &oldmask) == -1)) {
      perror("Failed to block signals to set up handlers");
      return 1;
   }
   printf("This is process %ld waiting for SIGUSR1 (%d)\n",
           (long)getpid(), SIGUSR1);

   act.sa_handler = showit;
   act.sa_flags = 0;
   if ((sigemptyset(&act.sa_mask) == -1) ||
       (sigaction(SIGUSR1, &act, NULL) == -1)) {
      perror("Failed to set up signal handler");
      return 1;
   }
   if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
      perror("Failed to unblock signals"); 
      return 1; 
   } 
   for ( ; ; )
      pause();
}
