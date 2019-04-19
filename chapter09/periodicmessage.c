#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define BILLION 1000000000L
#define TIMER_MSG "Received Timer Interrupt\n"

/* ARGSUSED */
static void interrupt(int signo, siginfo_t *info, void *context) {
   int errsave;

   errsave = errno;
   write(STDOUT_FILENO, TIMER_MSG, sizeof(TIMER_MSG) - 1);
   errno = errsave;
}

static int setinterrupt() { 
   struct sigaction act;

   act.sa_flags = SA_SIGINFO;
   act.sa_sigaction = interrupt;
   if ((sigemptyset(&act.sa_mask) == -1) ||
       (sigaction(SIGALRM, &act, NULL) == -1))
      return -1;
   return 0;
}

static int setperiodic(double sec) {
   timer_t timerid;
   struct itimerspec value;

   if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1)
      return -1;
   value.it_interval.tv_sec = (long)sec;
   value.it_interval.tv_nsec = (sec - value.it_interval.tv_sec)*BILLION;
   if (value.it_interval.tv_nsec >= BILLION) {
      value.it_interval.tv_sec++;
      value.it_interval.tv_nsec -= BILLION;
   }
   value.it_value = value.it_interval;
   return timer_settime(timerid, 0, &value, NULL);
}

int main(void) {
   if (setinterrupt() == -1) {
      perror("Failed to setup SIGALRM handler");
      return 1;
   }
   if (setperiodic(2.0) == -1) {
      perror("Failed to setup periodic interrupt");
      return 1;
   }
   for ( ; ; )
      pause();
}
