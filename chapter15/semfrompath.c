#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#define PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define SET_SIZE 2
 
int main(int argc, char *argv[]) {
   key_t mykey;
   int semid;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s pathname id\n", argv[0]);
      return 1;
   }
   if ((mykey = ftok(argv[1], atoi(argv[2]))) == (key_t)-1) {
      fprintf(stderr, "Failed to derive key from filename %s:%s\n",
             argv[1], strerror(errno));
      return 1; 
   }
   if ((semid = semget(mykey, SET_SIZE, PERMS | IPC_CREAT)) == -1) {
      fprintf(stderr, "Failed to create semaphore with key %d:%s\n",
             (int)mykey, strerror(errno));
      return 1; 
   }
   printf("semid = %d\n", semid);
   return 0; 
}
