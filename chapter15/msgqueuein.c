#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include "msgqueuelog.h"
#include "restart.h"
#define MAXLINE 1024

int main(int argc, char *argv[]) {
   char buf[MAXLINE];
   int key;
   int size;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s key\n", argv[0]);
      return 1;
   }
   key = atoi(argv[1]);
   if (initqueue(key) == -1) {
      perror("Failed to initialize message queue");
      return 1;
   }
   if (msgprintf("This is process %ld\n", (long)getpid()) == -1) {
      perror("Failed to write header to message queue");
      return 1;
   }
   for ( ; ; ) {
      if ((size = readline(STDIN_FILENO, buf, MAXLINE)) == -1) {
         perror("Failed to read from standard input");
         break;
      }
      if (msgwrite(buf, size) == -1) {
         perror("Failed to write message to standard output");
         break;
      }
   }
   return 0;
}
