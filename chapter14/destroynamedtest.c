#include <semaphore.h>
#include <stdio.h>

int destroynamed(char *name, sem_t *sem);
int getnamed(char *name, sem_t ** sem, int val);

int main(int argc, char *argv[]) {
   sem_t *mysem;

   if (argc != 2) {
      fprintf(stderr, "Usage %s semname\n", argv[0]);
      return 1;
   }
   if (getnamed(argv[1], &mysem, 0) == -1) {
       perror("getnamed");
       return 1;
   }
   if (destroynamed(argv[1], mysem) == -1) {
      perror("first destroy failed");
      return 1;
   }
   fprintf(stderr,"Semaphore %s destroyed\n", argv[1]);
   if (destroynamed(argv[1], mysem) == -1) {
      perror("second destroy should have failed and did");
      return 0;
   }
   fprintf(stderr, "Destroy successful\n");
   return 1;
}
