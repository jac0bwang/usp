#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "asyncmonitorpoll.h"
 
void dowork(void);
void processbuffer(int which, char *buf, int bufsize);
 
int main(int argc, char *argv[]) {
   char *buf;
   int done[NUMOPS];
   int fd[NUMOPS];
   int i;
   int numbytes, numfiles;
                                
   if (argc < 2) {  
      fprintf(stderr, "Usage: %s filename1 filename2 ...\n", argv[0]);
      return 1; 
   } else if (argc > NUMOPS + 1) {
      fprintf(stderr, "%s: only supports %d simultaneous operations\n",
              argv[0],  NUMOPS);
      return 1;
   } 
   numfiles = argc - 1;
   
   for (i = 0; i < numfiles; i++)  {            /* set up the I/O operations */
      done[i] = 0; 
      if ((fd[i] = open(argv[i+1], O_RDONLY)) == -1) { 
         fprintf(stderr, "Failed to open %s:%s\n", argv[i+1], strerror(errno));
         return 1; 
      }
      if (initaio(fd[i], i) == -1) {
         fprintf(stderr, "Failed to setup I/O op %d:%s\n", i, strerror(errno));
         return 1;
      } 
      if (readstart(i) == -1) { 
         fprintf(stderr, "Failed to start read %d:%s\n", i, strerror(errno));
         return 1;
      } 
   }
   for (  ;  ;  ) {                                         /* loop and poll */
      dowork(); 
      for (i = 0; i < numfiles; i++) {
         if (done[i])
            continue;
         numbytes = readcheck(i, &buf);
         if ((numbytes == -1) && (errno == EINPROGRESS))
            continue;
         if (numbytes <= 0) {
            if (numbytes == 0)
               fprintf(stderr, "End of file on %d\n", i);
            else
               fprintf(stderr, "Failed to read %d:%s\n", i, strerror(errno));
            done[i] = 1;
            continue;
         }
         processbuffer(i, buf, numbytes);
         reinit(i);
         if (readstart(i) == -1) { 
            fprintf(stderr, "Failed to start read %d:%s\n", i, strerror(errno));
            done[i] = 1;
         }
      }
   }
}
