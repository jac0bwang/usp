#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int pid;
   int signo;
   int sval;
   union sigval value;

   if (argc != 4) {
      fprintf(stderr, "Usage: %s pid signal value\n", argv[0]);
      return 1; 
   }
   pid = atoi(argv[1]);
   signo = atoi(argv[2]);
   sval = atoi(argv[3]);
   fprintf(stderr, "Sending signal %d with value %d to process %d\n",
                    signo, sval, pid);
   value.sival_int = sval;
   if (sigqueue(pid, signo, value) == -1) {
      perror("Failed to send the signal");
      return 1;
   }
   return 0;
}
