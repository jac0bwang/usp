#include <stdio.h>
#include <unistd.h>

void show_return_status();

int main(void) {

   int childpid;

   childpid = fork();
   if (childpid == -1) {
      perror("Could not fork");
      return 1;
   }
   if (childpid > 0)
      show_return_status();
   else {
      fprintf(stderr,"Child process %ld about to sleep\n",(long)getpid());
      sleep(5);
      fprintf(stderr,"Child process %ld about to exit\n",(long)getpid());
   }
   return 0;
}
