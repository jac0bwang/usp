#include <sys/sem.h>
 
int removesem(int semid) {
   return semctl(semid, 0, IPC_RMID);
}
