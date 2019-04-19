#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 1024

int main  (int argc, char *argv[]) {
   char buffer[BUFSIZE];
   char *c;
   pid_t childpid = 0;
   int i, n;
   sem_t semlock;

   if (argc != 2){   /* check for valid number of command line arguments */
      fprintf (stderr, "Usage: %s processes\n", argv[0]);
      return 1;
   }

   if (sem_init(&semlock, 0, 1) == -1) {
      perror("Failed to create unnamed semlock");
      return 1;
   }
   n = atoi(argv[1]);
   for (i = 1; i < n; ++i)
      if (childpid = fork())
         break;
   snprintf(buffer, BUFSIZE,
            "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
            i, (long)getpid(), (long)getppid(), (long)childpid);
   c = buffer;

   while (sem_wait(&semlock) == -1)   /* Entry section  */ 
       if (errno != EINTR) { 
          fprintf(stderr, "[%ld] Failed to lock semlock:%s\n",
                  (long)getpid(), strerror(errno));
          return 1;
       }
   /*****************start of critical section ********************/
   while (*c != '\0') {
      fputc(*c, stderr);
      for (i=0;i<100000;i++) ;
      c++;
   }
   /*******************end of critical section ********************/
   if (sem_post(&semlock) == -1) {     /* Exit section */
      fprintf(stderr, "[%ld] Failed to unlock semlock:%s\n",
              (long)getpid(), strerror(errno));
      return 1;
   }
   return 0;
}
