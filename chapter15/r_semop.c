#include <errno.h>
#include <sys/sem.h>

int r_semop(int semid, struct sembuf *sops, int nsops) {
   while (semop(semid, sops, nsops) == -1) 
      if (errno != EINTR) 
         return -1;
   return 0; 
}
