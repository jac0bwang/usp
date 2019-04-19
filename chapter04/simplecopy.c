#include <stdio.h>
#include <unistd.h>

int copyfile(int fromfd, int tofd);

int main (void) {
   int numbytes;

   numbytes = copyfile(STDIN_FILENO, STDOUT_FILENO);
   fprintf(stderr, "Number of bytes copied: %d\n", numbytes);
   return 0;
}
