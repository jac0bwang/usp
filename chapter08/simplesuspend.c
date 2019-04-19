#include <errno.h>
#include <signal.h>
#include <unistd.h>

static int isinitialized = 0;
static struct sigaction oact; 
static int signum = 0;
static volatile sig_atomic_t sigreceived = 0;  

/* ARGSUSED */
static void catcher (int signo) {
    sigreceived = 1;
}

int initsuspend (int signo) {        /* set up the handler for the pause */
   struct sigaction act;
   if (isinitialized)
      return 0; 
   act.sa_handler = catcher;
   act.sa_flags = 0;
   if ((sigfillset(&act.sa_mask) == -1) ||
       (sigaction(signo, &act, &oact) == -1))
      return -1;
   signum = signo;
   isinitialized = 1;
   return 0;
} 
   
int restore(void) {
   if (!isinitialized)
      return 0;
   if (sigaction(signum, &oact, NULL) == -1)
      return -1;
   isinitialized = 0; 
   return 0; 
} 

int simplesuspend(void) {
   sigset_t maskblocked, maskold, maskunblocked;
   if (!isinitialized) {
      errno = EINVAL;
      return -1;
   }
   if ((sigprocmask(SIG_SETMASK, NULL, &maskblocked) == -1) ||
       (sigaddset(&maskblocked, signum) == -1) ||
       (sigprocmask(SIG_SETMASK, NULL, &maskunblocked) == -1) ||
       (sigdelset(&maskunblocked, signum) == -1) ||
       (sigprocmask(SIG_SETMASK, &maskblocked, &maskold) == -1))
       return -1;
   while(sigreceived == 0)
      sigsuspend(&maskunblocked);
   sigreceived = 0;
   return sigprocmask(SIG_SETMASK, &maskold, NULL);
}
