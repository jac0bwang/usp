#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "restart.h"

#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_CREAT | O_EXCL)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
 
int main(int argc, char *argv[]) {
   int bytes;
   int fromfd, tofd;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s from_file to_file\n", argv[0]);
      return 1;
   }
 
   if ((fromfd = open(argv[1], READ_FLAGS)) == -1) {
      perror("Failed to open input file");
      return 1; 
   }
 
   if ((tofd = open(argv[2], WRITE_FLAGS, WRITE_PERMS)) == -1) {
      perror("Failed to create output file");
      return 1;
   }
 
   bytes = copyfile(fromfd, tofd);
   printf("%d bytes copied from %s to %s\n", bytes, argv[1], argv[2]); 
   return 0;                                   /* the return closes the files */ 
}
