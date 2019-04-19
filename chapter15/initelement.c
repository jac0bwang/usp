#include <sys/sem.h>
 
int initelement(int semid, int semnum, int semvalue) {
   union semun {
      int val;
      struct semid_ds *buf;
      unsigned short *array;
   } arg;
   arg.val = semvalue;
   return semctl(semid, semnum, SETVAL, arg);
}
