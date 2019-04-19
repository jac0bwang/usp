#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"

int add(double x);
int initshared(int key);

int main(int argc, char *argv[]) {
   int bytesread;
   int fd;
   int key;

   if (argc != 3) {
      fprintf(stderr,"Usage: %s file key\n",argv[0]);
      return 1;
   }
   if ((fd = open(argv[1],O_RDONLY)) == -1) {
      perror("Failed to open file");
      return 1;
   }
   key = atoi(argv[2]);
   if (initshared(key) == -1) {
      perror("Failed to initialize shared sum");
      return 1;
   }
   while ((bytesread = readwrite(fd, STDOUT_FILENO)) > 0)
      if (add((double)bytesread) == -1) {
         perror("Failed to add to count");
         return 1;
      }
   return 0;
}
