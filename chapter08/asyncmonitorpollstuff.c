#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int ignore_sigpipe() {
   struct sigaction act;

   if (sigaction(SIGPIPE, (struct sigaction *)NULL, &act) < 0)
      return 1;
   if (act.sa_handler == SIG_DFL) {
      act.sa_handler = SIG_IGN;
      if (sigaction(SIGPIPE, &act, (struct sigaction *)NULL) < 0)
         return 1;
   }
   return 0;
}


void dowork(void) {
   ignore_sigpipe();
   sleep(3);
}

void processbuffer(int which, char *buf, int bufsize) {
   printf("Buffer %d follows\n",which);
   write(STDOUT_FILENO, buf, bufsize);
}
