#include <errno.h>
#include <limits.h>
#include <pwd.h>  
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "notifyonoff.h"
#define MAILDIR "/var/mail/"

static int checkmail(char *filename) {               /* is there new mail ? */ 
   struct stat buf; 
   int error = 0;
   static long newsize = 0;
   static long oldsize = 0;

   error = stat(filename, &buf);                   /* check the file status */
   if ((error == -1) && (errno != ENOENT)) 
      return -1;                       /* real error indicated by -1 return */
   if (!error) 
       newsize = (long)buf.st_size;
   else
       newsize = 0;
   if (newsize > oldsize)
      error = 1;                           /* return 1 to indicate new mail */
   else
      error = 0;                        /* return 0 to indicate no new mail */
   oldsize = newsize;
   return error;
}

int main(int argc, char *argv[]) {
   int check;
   char mailfile[PATH_MAX];
   struct passwd *pw;
   int sleeptime;
 
   if (argc != 2) {
      fprintf(stderr, "Usage: %s sleeptime\n", argv[0]);
      return 1;
   }
   sleeptime = atoi(argv[1]);
   if ((pw = getpwuid(getuid())) == NULL) { 
      perror("Failed to determine login name");
      return 1;
   }
   if (initnotify(SIGUSR1, SIGUSR2) == -1) {
      perror("Failed to set up turning on/off notification");
      return 1;
   }
   snprintf(mailfile, PATH_MAX,"%s%s",MAILDIR,pw->pw_name);

   for( ; ; ) {
      waitnotifyon();
      sleep(sleeptime);
      if ((check = checkmail(mailfile)) == -1) {
         perror("Failed to check mail file");
         break;
      }
      if (check)
         fprintf(stderr, "\007"); 
   }
   return 1;
}
