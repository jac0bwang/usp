#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int pid;
   int sig;
   if (argc != 3) {
       fprintf(stderr, "Usage: %s pid signal\n", argv[0]);
       return 1; 
   }
   pid = atoi(argv[1]);
   sig = atoi(argv[2]);
   while (kill(pid, sig) == 0) ;
   return 0;
}
