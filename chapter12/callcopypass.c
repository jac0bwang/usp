#include <errno.h>
#include <fcntl.h>
#include <pthread.h> 
#include <stdio.h>
#include <string.h> 
#include <sys/stat.h>
#include <sys/types.h>
#define PERMS (S_IRUSR | S_IWUSR)
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
void *copyfilepass(void *arg);
 
int main (int argc, char *argv[]) {
   int *bytesptr;
   int error; 
   int targs[3];
   pthread_t tid;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s fromfile tofile\n", argv[0]);
      return 1;
   }

   if (((targs[0] = open(argv[1], READ_FLAGS)) == -1) ||
       ((targs[1] = open(argv[2], WRITE_FLAGS, PERMS)) == -1)) {
      perror("Failed to  open the files");
      return 1;
   }
   if (error = pthread_create(&tid, NULL, copyfilepass, targs)) {
      fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
      return 1;
   }
   if (error = pthread_join(tid, (void **)&bytesptr)) {
      fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
      return 1;
   }
   printf("Number of bytes copied: %d\n", *bytesptr);
   return 0;
}
