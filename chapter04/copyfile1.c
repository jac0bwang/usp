#include <errno.h> 
#include <unistd.h>
#define BLKSIZE 1024

int copyfile(int fromfd, int tofd) {
   char *bp;
   char buf[BLKSIZE]; 
   int bytesread;
   int byteswritten = 0;
   int totalbytes = 0;

   for (  ;  ;  ) {
      while (((bytesread = read(fromfd, buf, BLKSIZE)) == -1) && 
             (errno == EINTR)) ;         /* handle interruption by signal */
      if (bytesread <= 0)          /* real error or end-of-file on fromfd */
         break;     
      bp = buf; 
      while (bytesread > 0) {    
         while(((byteswritten = write(tofd, bp, bytesread)) == -1 ) &&
              (errno == EINTR)) ;        /* handle interruption by signal */
         if (byteswritten < 0)                      /* real error on tofd */
            break;
         totalbytes += byteswritten;
         bytesread -= byteswritten;
         bp += byteswritten;     
      }
      if (byteswritten == -1)                       /* real error on tofd */
          break;
   }
   return totalbytes;
}
