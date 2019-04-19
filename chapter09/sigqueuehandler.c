#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void my_handler(int signo, siginfo_t* info, void *context) {
   char *code = NULL; 

   switch(info->si_code) {
      case SI_USER:     code = "USER"; break;
      case SI_QUEUE:    code = "QUEUE"; break;
      case SI_TIMER:    code = "TIMER"; break;
      case SI_ASYNCIO:  code = "ASYNCIO"; break;
      case SI_MESGQ:    code = "MESGQ"; break;
      default:          code = "Unknown";
   }
   fprintf(stderr, "Signal handler entered for signal number %d\n", signo);
   fprintf(stderr, "Signal=%3d, si_signo=%3d, si_code=%d(%s), si_value=%d\n",
          signo, info->si_signo, info->si_code, code, info->si_value.sival_int);
}

int main(void) {
   struct sigaction act;
 
   fprintf(stderr, "Process ID is %ld\n", (long)getpid());
   fprintf(stderr, "Setting up signal SIGUSR1 = %d ready\n", SIGUSR1);

   act.sa_flags = SA_SIGINFO;
   act.sa_sigaction = my_handler;
   if ((sigemptyset(&act.sa_mask) == -1) ||
       (sigaction(SIGUSR1, &act, NULL) == -1)) {
      perror("Failed to set up SIGUSR1 signal");
      return 1; 
   }   
   /* no fprintf calls from here on */ 
   for( ; ; )
      pause();
}
