#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   struct sigaction ignore;

   if (argc != 2) {
      fprintf(stderr,"Usage: %s string \n",argv[0]);
      return 1;
   }
   ignore.sa_flags = 0;
   ignore.sa_handler = SIG_IGN;
   if ( (sigemptyset(&ignore.sa_mask) == -1) ||
        (sigaction(SIGINT, &ignore, NULL) == -1) ) {
      fprintf(stderr, "Cannot ignore SIGINT\n");
      return 1;
   }

   fprintf(stderr,"%s: pid=%5d pgid=%5d psid=%5d ppid=%5d\n",
         argv[1],(int)getpid(),(int)getpgrp(),(int)getsid(0),(int)getppid());
   sleep(100);
   return 0;
}
