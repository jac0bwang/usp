#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "restart.h"
#define PERM (S_IRUSR | S_IWUSR)

int detachandremove(int shmid, void *shmaddr);

int main(int argc, char *argv[]) {
   int bytesread;
   int childpid;
   int fd, fd1, fd2;
   int id;
   int *sharedtotal;
   int totalbytes = 0;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
      return 1;
   }
   if (((fd1 = open(argv[1], O_RDONLY)) == -1) || 
       ((fd2 = open(argv[2], O_RDONLY)) == -1)) {
      perror("Failed to open file"); 
      return 1;
   }
   if ((id = shmget(IPC_PRIVATE, sizeof(int), PERM)) == -1) {
      perror("Failed to create shared memory segment");
      return 1;
   }
   if ((sharedtotal = (int *)shmat(id, NULL, 0)) == (void *)-1) {
      perror("Failed to attach shared memory segment");
      if (shmctl(id, IPC_RMID, NULL) == -1)
         perror("Failed to  remove memory segment");
      return 1;
   }
   if ((childpid = fork()) == -1) {
      perror("Failed to create child process");
      if (detachandremove(id, sharedtotal) == -1)
         perror("Failed to destroy shared memory segment");
      return 1;
   }
   if (childpid > 0)                                         /* parent code */
      fd = fd1;
   else
      fd = fd2;
   while ((bytesread = readwrite(fd, STDOUT_FILENO)) > 0)
      totalbytes += bytesread;
   if (childpid == 0) {                                      /* child code */
      *sharedtotal = totalbytes;
      return 0;
   }
   if (r_wait(NULL) == -1) 
      perror("Failed to wait for child");
   else {
      fprintf(stderr, "Bytes copied: %8d by parent\n", totalbytes);
      fprintf(stderr, "              %8d by child\n", *sharedtotal);
      fprintf(stderr, "              %8d total\n", totalbytes + *sharedtotal);
   }
   if (detachandremove(id, sharedtotal) == -1) {
      perror("Failed to destroy shared memory segment");
      return 1;
   }
   return 0;
}
