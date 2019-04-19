#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "restart.h"

#define BUFSIZE 1000
#define MSG "Got Ctrl-C\n"
#define MSG_LEN sizeof(MSG)

/* ARGSUSED */
static void handler(int signo) {
   r_write(STDOUT_FILENO, MSG, MSG_LEN);
}

int main(void) {
   char buf[BUFSIZE];
   int i;
   int num;
   struct sigaction act;

   act.sa_handler = handler;
   act.sa_flags = 0;
   sigemptyset(&act.sa_mask);
   if (sigaction(SIGINT, &act, NULL) == -1) {
      fprintf(stderr, "Error setting up signal handler\n");
      return 1;
   }
   for (i=0; i<5; i++) {
      num = readtimed(STDIN_FILENO,buf,BUFSIZE,10.0);
      if (num == 0)
          break;
      if (num < 0) {
         perror("readtimed returned an error");
         continue;
      }
      fprintf(stderr,"Got %d bytes\n",num);
   }
   return 0;
}
