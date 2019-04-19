#include <errno.h>
#include <poll.h> 
#include <stdlib.h>
#include <stropts.h>
#include <unistd.h>  
#include "restart.h"
#define BUFSIZE 1024

void docommand(char *, int);

void monitorpoll(int fd[], int numfds)  {
   char buf[BUFSIZE];
   int bytesread;
   int i;
   int numnow = 0;
   int numready;
   struct pollfd *pollfd;

   for (i=0; i< numfds; i++)             /* initialize the polling structure */
      if (fd[i] >= 0)
          numnow++;
   if ((pollfd = (void *)calloc(numfds, sizeof(struct pollfd))) == NULL)
      return;
   for (i = 0; i < numfds; i++) {
      (pollfd + i)->fd = *(fd + i);
      (pollfd + i)->events = POLLRDNORM;
   }
   while (numnow > 0) {        /* Continue monitoring until descriptors done */
      numready = poll(pollfd, numfds, -1); 
      if ((numready == -1) && (errno == EINTR))
         continue;                /* poll interrupted by a signal, try again */
      else if (numready == -1)            /* real poll error, can't continue */
         break;
      for (i = 0; i < numfds && numready > 0; i++)  {
         if ((pollfd + i)->revents) {
            if ((pollfd + i)->revents & (POLLRDNORM | POLLIN) ) {
               bytesread = r_read(fd[i], buf, BUFSIZE);
               numready--;
               if (bytesread > 0)
                  docommand(buf, bytesread);
               else
                  bytesread = -1;                             /* end of file */
            } else if ((pollfd + i)->revents & (POLLERR | POLLHUP))
               bytesread = -1;
            else                    /* descriptor not involved in this round */
               bytesread = 0;
            if (bytesread == -1) {      /* error occurred, remove descriptor */
               r_close(fd[i]);
               (pollfd + i)->fd = -1; 
               numnow--; 
            }
         }     
      }      
   }
   for (i = 0; i < numfds; i++)
       r_close(fd[i]);
   free(pollfd);
}
