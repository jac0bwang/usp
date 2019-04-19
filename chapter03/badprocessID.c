#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
   pid_t childpid;
   pid_t mypid;

   mypid = getpid();
   childpid = fork();
   if (childpid == -1) {
      perror("Failed to fork");
      return 1;
   }
   if (childpid == 0)                                   /* child code */
      printf("I am child %ld, ID = %ld\n", (long)getpid(), (long)mypid);
   else                                                /* parent code */ 
      printf("I am parent %ld, ID = %ld\n", (long)getpid(), (long)mypid);
   return 0;
}
