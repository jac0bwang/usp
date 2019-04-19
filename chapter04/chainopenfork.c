#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define CREATE_PERMS (S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH)

int main  (int argc, char *argv[]) {
   char buf[BUFSIZE];
   pid_t childpid = 0; 
   int fd;
   int i, n;
 
   if (argc != 3){       /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes filename\n", argv[0]);
      return 1;
   }     
                                        /* open the log file before the fork */
   fd = open(argv[2], CREATE_FLAGS, CREATE_PERMS);
   if (fd < 0) {
      perror("Failed to open file");
      return 1;
   }
   n = atoi(argv[1]);                              /* create a process chain */
   for (i = 1; i < n; i++)
       if (childpid = fork())
          break;
   if (childpid == -1) {
      perror("Failed to fork");
      return 1;
   }     
                                       /* write twice to the common log file */
   sprintf(buf, "i:%d process:%ld ", i, (long)getpid());
   write(fd, buf, strlen(buf));
   sprintf(buf, "parent:%ld child:%ld\n", (long)getppid(), (long)childpid);
   write(fd, buf, strlen(buf));
   return 0;
}
