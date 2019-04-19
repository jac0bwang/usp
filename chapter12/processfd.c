#include <stdio.h>
#include "restart.h"
#define BUFSIZE 1024

void docommand(char *cmd, int cmdsize);

void *processfd(void *arg) { /* process commands read from file descriptor */ 
   char buf[BUFSIZE];
   int fd;
   ssize_t nbytes;

   fd = *((int *)(arg));
   for ( ; ; )  {
      if ((nbytes = r_read(fd, buf, BUFSIZE)) <= 0)
         break;
      docommand(buf, nbytes);
   }
   return NULL;
}
