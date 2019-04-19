#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#define MAILFILE "/var/mail/ostudent"
#define SLEEPTIME 10
 
int main(void) {
   int mailfd;
 
   for( ; ; ) {
      if ((mailfd = open(MAILFILE, O_RDONLY)) != -1) {
         fprintf(stderr, "%s", "\007");
         while ((close(mailfd) == -1) && (errno == EINTR)) ;
      }  
      sleep(SLEEPTIME);
   }
}
