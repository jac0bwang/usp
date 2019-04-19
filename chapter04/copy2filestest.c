#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int copy2files(int fromfd1, int tofd1, int fromfd2, int tofd2);

int main(int argc, char *argv[]) {
   int bytescopied;
   int fd1, fd2;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
      return 1;
   }
   if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
      fprintf(stderr, "Failed to open file %s:%s\n", argv[1], strerror(errno));
      return 1;
   }
   if ((fd2 = open(argv[2], O_RDONLY)) == -1) {
      fprintf(stderr, "Failed to open file %s:%s\n", argv[2], strerror(errno));
      return 1;
   }
   bytescopied = copy2files(fd1, STDOUT_FILENO, fd2, STDOUT_FILENO);
   fprintf(stderr, "Bytes copied: %d\n", bytescopied);
   return 0;
}
