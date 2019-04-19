#include <signal.h>

static int sigreceived = 0;

void wait_for_signal() {
   sigset_t sigall, sigmost, sigold;
   int signum = SIGUSR1;

   sigprocmask(SIG_SETMASK, NULL, &sigold);
   sigfillset(&sigall);
   sigfillset(&sigmost);
   sigdelset(&sigmost, signum);
   sigprocmask(SIG_SETMASK, &sigall, NULL);
   if (sigreceived == 0)
        sigsuspend(&sigmost);
   sigprocmask(SIG_SETMASK, &sigold, NULL);
}
