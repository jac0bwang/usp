#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
   char c = '!';
   int myfd;

   if ((myfd = open("my.dat", O_RDONLY)) == -1) {
      perror("Failed to open file");
      return 1;
   }
   if (fork() == -1) {
      perror("Failed to fork");
      return 1;
   }
   read(myfd, &c, 1);
   printf("Process %ld got %c\n", (long)getpid(), c);
   return 0;
}
