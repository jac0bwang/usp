#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void) {
   pid_t childpid;
                          /* set up signal handlers here ... */
   childpid = fork();
   if (childpid == -1) {
      perror("Failed to fork");
      return 1;
   }
   if (childpid == 0)
      fprintf(stderr, "I am child %ld\n", (long)getpid());
   else if (wait(NULL) != childpid)
      fprintf(stderr, "A signal must have interrupted the wait!\n");
   else
      fprintf(stderr, "I am parent %ld with child %ld\n", (long)getpid(),
           (long)childpid);
   return 0;
}
