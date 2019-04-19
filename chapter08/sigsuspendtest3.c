#include <signal.h>

void wait_for_sginal() {
   int sigreceived = 0;  
 
   sigset_t masknew, maskold;
   int signum = SIGUSR1;    
 
   sigprocmask(SIG_SETMASK, NULL, &maskold);
   sigprocmask(SIG_SETMASK, NULL, &masknew);
   sigaddset(&masknew, signum);
   sigprocmask(SIG_SETMASK, &masknew, NULL);
   sigdelset(&masknew, signum);
   while(sigreceived == 0)
       sigsuspend(&masknew);
   sigprocmask(SIG_SETMASK, &maskold, NULL);
}
