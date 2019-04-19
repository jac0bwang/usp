#include <errno.h>
#include <semaphore.h>
#define BARRIER_LOCK "/semlock"
#define BARRIER_WAIT "/semwait"
#define PERMS = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

int destroynamed(char *name, sem_t *sem);
int getnamed(char *name, sem_t **sem, int val);

static volatile int barriercount = 0;
static int barriersize = 0;
static sem_t *block;
static sem_t *bwait;

#include <stdio.h>

int destroybarrier(void) {  /* try to destroy both semaphores for the barrier */
   int error = 0;
   if (destroynamed(BARRIER_LOCK, block) == -1) 
      error = errno;
   if ((destroynamed(BARRIER_WAIT, bwait) != -1) && !error)
      return 0;
   if (error)
      errno = error;
   return -1;
}

int initbarrier(int n) {
   int error = 0;
   if (n <= 0)  {    /* barrier must have a positive size */
      errno = EINVAL;
      return -1;
   }
   if (getnamed(BARRIER_LOCK, &block, 1) == -1)  /* access the semaphores */
      return -1;
   if (getnamed(BARRIER_WAIT, &bwait, 0) == -1) {
      error = errno;
      destroynamed(BARRIER_LOCK, block);  
      errno = error;
      return -1;
   }

   while (sem_wait(block) == -1)  /* lock the barrier */
      if (errno != EINTR)
         return -1;
   if (barriersize == 0)          /* barriersize only initialized once */
      barriersize = n;
   else if (barriersize != n)      
      error = EINVAL;
   if (!sem_post(block) && !error)
      return 0;
   if (error) 
      errno = error;   /* set errno to first error that occurred */
    return -1;
}
   
int waitbarrier(void) {
   int numwaiting = 0;
   int thesize = 0;

   fprintf(stderr,"Entered waitbarrier\n");
   while (sem_wait(block) == -1)  /* lock the barrier */
      if (errno != EINTR)
         return -1;
   barriercount++;
   numwaiting = barriercount;
   fprintf(stderr,"Num waiting is %d\n",barriercount);
   thesize = barriersize;
   if (sem_post(block) == -1)
      return -1;
   if (numwaiting < thesize)    /* wait at the barrier */
      while (sem_wait(bwait) == -1) 
          if (errno != EINTR)
              return -1;
   if (sem_post(bwait) == -1)  /* failed to release barrier access */
      return -1;
   return 0;
}
