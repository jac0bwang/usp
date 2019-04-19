#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "restart.h"
 
int main(void) {
   char bufout[] = "hello"; 
   char bufin[10] = "empty";
   pid_t childpid;  
   int fd[2]; 
    
   if (pipe(fd) == -1) {
      perror("failed to create the pipe"); 
      return 1; 
   } else if ((childpid = fork()) == -1) {
      perror("failed to fork"); 
      return 1;
   }
   if (childpid) {   /* parent code */
      close(fd[0]);
      copyfile(STDIN_FILENO, fd[1]);
   }
   else {            /* child code */
      close(fd[1]);
      copyfile(fd[0], STDOUT_FILENO);
   }
   fprintf(stderr,"[%ld]: my bufin is {%s}, my bufout is {%s}\n",
           (long)getpid(), bufin, bufout); 
   return 0;
}

