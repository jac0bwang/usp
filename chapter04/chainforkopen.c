#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024
#define FILE_PERMS (S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH)
#define FILE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)

int main  (int argc, char *argv[]) {
   char buf[BUFSIZE];
   pid_t childpid = 0; 
   int fd;
   int i, n;
 
   if (argc != 3){   /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes filename\n", argv[0]);
      return 1;
   }     
                     /* Create a process chain */
   n = atoi(argv[1]);
   for (i = 1; i < n;  ++i)
       if (childpid = fork())
          break;
   if (childpid == -1) {
      perror("The fork failed");
      return 1;
   }     
                      /* Open the log file after the fork */
   fd = open(argv[2], FILE_FLAGS, FILE_PERMS);
   if (fd < 0) {
      perror("Open failed");
      return 1;
   }
                    /* Write twice to the common log file */
   sprintf(buf, "i:%d process:%ld ", i, (long)getpid());
   write(fd, buf, strlen(buf));
   sprintf(buf,"parent:%ld child:%ld\n", (long)getppid(), (long)childpid);
   write(fd, buf, strlen(buf));
   return 0;
}
