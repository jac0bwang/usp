#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#define COUNT 1000
#define MILLION 1000000L

static int count = 0;

/* ARGSUSED */
static void handler(int signo, siginfo_t *info, void *context) {
   count++;
}

int main(void) {
   struct sigaction act;
   sigset_t sigblocked, sigunblocked;
   long tdif;
   struct timeval tend, tstart;

   act.sa_flags = SA_SIGINFO;
   act.sa_sigaction = handler;
   if ((sigemptyset(&act.sa_mask) == -1) || 
       (sigaction(SIGALRM, &act, NULL) == -1)) {
      perror("Failed to set up handler for SIGALRM");
      return 1;
   }
   if ((sigemptyset(&sigblocked) == -1) ||
       (sigemptyset(&sigunblocked) == -1) ||
       (sigaddset(&sigblocked, SIGALRM) == -1) ||
       (sigprocmask(SIG_BLOCK, &sigblocked, NULL) == -1)) {
      perror("Failed to block signal");
      return 1;
   }
   printf("Process %ld waiting for first SIGALRM (%d) signal\n",
           (long)getpid(), SIGALRM);
   sigsuspend(&sigunblocked);
   if (gettimeofday(&tstart, NULL) == -1) {
      perror("Failed to get start time");
      return 1;
   }
   while (count <= COUNT)
      sigsuspend(&sigunblocked);
   if (gettimeofday(&tend, NULL) == -1) {
      perror("Failed to get end time");
      return 1;
   }
   tdif = MILLION*(tend.tv_sec - tstart.tv_sec) +
                   tend.tv_usec - tstart.tv_usec;
   printf("Got %d signals in %ld microseconds\n", count-1, tdif);
   return 0;
}
