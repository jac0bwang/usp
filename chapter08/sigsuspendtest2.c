#include <signal.h>

void wait_for_signal() {
   int sigreceived = 0;  
 
   sigset_t maskblocked, maskold, maskunblocked;
   int signum = SIGUSR1;
 
   sigprocmask(SIG_SETMASK, NULL, &maskold);
   sigprocmask(SIG_SETMASK, NULL, &maskblocked);
   sigprocmask(SIG_SETMASK, NULL, &maskunblocked);
   sigaddset(&maskblocked, signum);
   sigdelset(&maskunblocked, signum);
   sigprocmask(SIG_BLOCK, &maskblocked, NULL);
   while(sigreceived == 0)
       sigsuspend(&maskunblocked);
   sigprocmask(SIG_SETMASK, &maskold, NULL);
}
