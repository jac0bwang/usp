#include <errno.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/select.h>
#include <sys/types.h>
#include "restart.h"
#define BUFSIZE 1024
void docommand(char *, int);

void monitorselect(int fd[], int numfds) {
   char buf[BUFSIZE];
   int bytesread;
   int i;
   int maxfd;
   int numnow, numready;
   fd_set readset;

   maxfd = 0;                  /* set up the range of descriptors to monitor */
   for (i = 0; i < numfds; i++) {
       if ((fd[i] < 0) || (fd[i] >= FD_SETSIZE))
          return;
       if (fd[i] >= maxfd)
          maxfd = fd[i] + 1;
   }
   numnow = numfds;
   while (numnow > 0) {            /* continue monitoring until all are done */
      FD_ZERO(&readset);                  /* set up the file descriptor mask */
      for (i = 0; i < numfds; i++) 
         if (fd[i] >= 0)
            FD_SET(fd[i], &readset);
      numready = select(maxfd, &readset, NULL, NULL, NULL);  /* which ready? */
      if ((numready == -1) && (errno == EINTR))     /* interrupted by signal */
         continue;   
      else if (numready == -1)                          /* real select error */
         break; 
      for (i = 0; (i < numfds) && (numready > 0); i++) { /* read and process */
         if (fd[i] == -1)                         /* this descriptor is done */
            continue;
         if (FD_ISSET(fd[i], &readset)) {        /* this descriptor is ready */
            bytesread = r_read(fd[i], buf, BUFSIZE);
            numready--;
            if (bytesread > 0)
               docommand(buf, bytesread);
            else  {           /* error occurred on this descriptor, close it */
               r_close(fd[i]);
               fd[i] = -1;
               numnow--;
            }
         }
      }
   }        
   for (i = 0; i < numfds; i++)
       if (fd[i] >= 0)
           r_close(fd[i]);
}
