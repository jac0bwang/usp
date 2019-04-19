#include <signal.h>
#include <stdio.h>
 
int testignored(int signo) {
   struct sigaction act;
   if ((sigaction(signo, NULL, &act) == -1) || (act.sa_handler != SIG_IGN))
      return 0;
   return 1;
}
