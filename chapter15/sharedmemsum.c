#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define PERM (S_IRUSR | S_IWUSR)

int initsemset(key_t mykey, int value, sig_atomic_t *readyp);
void setsembuf(struct sembuf *s, int num, int op, int flg);

typedef struct {
   int count;
   double sum;
   sig_atomic_t ready;
} shared_sum_t;

static int semid;
static struct sembuf semlock;
static struct sembuf semunlock;
static shared_sum_t *sharedsum;

int initshared(int key) {              /* initialize shared memory segment */
   int shid;

   setsembuf(&semlock, 0, -1, 0);         /* setting for locking semaphore */
   setsembuf(&semunlock, 0, 1, 0);      /* setting for unlocking semaphore */
                          /* get attached memory, creating it if necessary */
   shid = shmget(key, sizeof(shared_sum_t), PERM | IPC_CREAT | IPC_EXCL);
   if ((shid == -1) && (errno != EEXIST))                    /* real error */
      return -1;
   if (shid == -1) {              /* already created, access and attach it */
      if (((shid = shmget(key, sizeof(shared_sum_t), PERM)) == -1) ||
          ((sharedsum = (shared_sum_t *)shmat(shid, NULL, 0)) == (void *)-1) )
         return -1;
   }
   else {    /* successfully created, must attach and initialize variables */
      sharedsum = (shared_sum_t *)shmat(shid, NULL, 0);
      if (sharedsum == (void *)-1)
         return -1;
      sharedsum -> count = 0;
      sharedsum -> sum = 0.0;
   }
   semid = initsemset(key, 1, &sharedsum->ready);
   if (semid == -1)
      return -1;
   return 0;
}

int add(double x) {                                       /* add x to sum */
   if (semop(semid, &semlock, 1) == -1)
      return -1;
   sharedsum -> sum += x;
   sharedsum -> count++;
   if (semop(semid, &semunlock, 1) == -1)
      return -1;
   return 0;
}

int getcountandsum(int *countp, double *sum) {    /* return sum and count */
   if (semop(semid, &semlock, 1) == -1)
      return -1;
   *countp = sharedsum -> count;
   *sum = sharedsum -> sum;
   if (semop(semid, &semunlock, 1) == -1)
      return -1;
   return 0;
}
