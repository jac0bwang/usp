#include <errno.h>
#include <semaphore.h>

static int shared = 0;
static sem_t sharedsem;

int initshared(int val) {   
   if (sem_init(&sharedsem, 0, 1) == -1)
      return -1;
   shared = val;
   return 0;
}

int getshared(int *sval) {
   while (sem_wait(&sharedsem) == -1)
      if (errno != EINTR)
         return -1;
   *sval = shared;
   return sem_post(&sharedsem);
}

int incshared() {
   while (sem_wait(&sharedsem) == -1)
      if (errno != EINTR) 
         return -1; 
   shared++;
   return sem_post(&sharedsem); 
} 
