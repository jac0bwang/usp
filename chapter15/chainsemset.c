#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "restart.h"
#define BUFSIZE 1024
#define PERMS (S_IRUSR | S_IWUSR)
 
int initelement(int semid, int semnum, int semvalue);
int r_semop(int semid, struct sembuf *sops, int nsops);
int removesem(int semid);  
void setsembuf(struct sembuf *s, int num, int op, int flg);

void printerror(char *msg, int error) {
   fprintf(stderr, "[%ld] %s: %s\n", (long)getpid(), msg, strerror(error));
}
 
int main (int argc, char *argv[]) {
   char buffer[MAX_CANON];
   char *c;
   pid_t childpid;
   int delay;
   int error;
   int i, j, n;
   int semid;
   struct sembuf semsignal[1];
   struct sembuf semwait[1];
 
   if ((argc != 3) || ((n = atoi(argv[1])) <= 0) ||
        ((delay = atoi(argv[2])) < 0))  {
      fprintf (stderr, "Usage: %s processes delay\n", argv[0]);
      return 1;
   }
                        /* create a semaphore containing a single element */
   if ((semid = semget(IPC_PRIVATE, 1, PERMS)) == -1) {
      perror("Failed to create a private semaphore"); 
      return 1; 
   }
   setsembuf(semwait, 0, -1, 0);                   /* decrement element 0 */
   setsembuf(semsignal, 0, 1, 0);                  /* increment element 0 */ 
   if (initelement(semid, 0, 1) == -1) {
      perror("Failed to initialize semaphore element to 1");  
      if (removesem(semid) == -1)
         perror("Failed to remove failed semaphore"); 
      return 1; 
   }
   for (i = 1; i < n; i++)
      if (childpid = fork())
         break;
   snprintf(buffer, BUFSIZE, "i:%d PID:%ld  parent PID:%ld  child PID:%ld\n",
           i, (long)getpid(), (long)getppid(), (long)childpid);
   c = buffer;
   /******************** entry section ************************************/
   if (((error = r_semop(semid, semwait, 1)) == -1) && (i > 1)) {
      printerror("Child failed to lock semid", error);
      return 1;
   }
   else if (!error) {
      /***************** start of critical section ************************/
      while (*c != '\0') {
         fputc(*c, stderr);
         c++;
         for (j = 0; j < delay; j++) ;
       }
      /***************** exit section ************************************/
      if ((error = r_semop(semid, semsignal, 1)) == -1)  
         printerror("Failed to unlock semid", error);
   } 
   /******************** remainder section *******************************/
   if ((r_wait(NULL) == -1) && (errno != ECHILD))
      printerror("Failed to wait", errno);
   if ((i == 1) && ((error = removesem(semid)) == -1)) {
      printerror("Failed to clean up", error); 
      return 1;
   } 
   return 0;
}
