#include <errno.h>
#include <signal.h> 
#include <stdio.h> 
#include <time.h> 
#include <sys/sem.h>
#include <sys/stat.h>
#define PERMS (S_IRUSR | S_IWUSR)
#define TEN_MILLION 10000000L
int initelement(int semid, int semnum, int semvalue);

int initsemset(key_t mykey, int value, sig_atomic_t *readyp) {
   int semid;
   struct timespec sleeptime;

   sleeptime.tv_sec = 0;
   sleeptime.tv_nsec = TEN_MILLION;
   semid = semget(mykey, 1, PERMS | IPC_CREAT | IPC_EXCL);
   if ((semid == -1) && (errno != EEXIST))         /* real error, so return */
      return -1;
   if (semid >= 0) {          /* we created the semaphore, so initialize it */
      if (initelement(semid, 0, value) == -1)
         return -1;
      *readyp = 1;
      return semid;
   }
   if ((semid = semget(mykey, 1, PERMS)) == -1)           /* just access it */
      return -1;
   while (*readyp == 0)                            /* wait for initialization */
      nanosleep(&sleeptime, NULL);
   return semid;
}
