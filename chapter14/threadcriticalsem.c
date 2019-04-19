#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define TEN_MILLION 10000000L
#define BUFSIZE 1024

void *threadout(void *args) {
   char buffer[BUFSIZE];
   char *c;
   sem_t *semlockp;
   struct timespec sleeptime;

   semlockp = (sem_t *)args;
   sleeptime.tv_sec = 0;
   sleeptime.tv_nsec = TEN_MILLION;
   snprintf(buffer, BUFSIZE, "This is a thread from process %ld\n",
           (long)getpid());
   c = buffer;
   /****************** entry section *******************************/
   while (sem_wait(semlockp) == -1)        /* Entry section */
      if(errno != EINTR) {
         fprintf(stderr, "Thread failed to lock semaphore\n");
         return NULL;
      }
   /****************** start of critical section *******************/
   while (*c != '\0') {
      fputc(*c, stderr);
      c++;
      nanosleep(&sleeptime, NULL);
   }
   /****************** exit section ********************************/
   if (sem_post(semlockp) == -1)         /* Exit section */
      fprintf(stderr, "Thread failed to unlock semaphore\n");
   /****************** remainder section ***************************/
   return NULL;
}
