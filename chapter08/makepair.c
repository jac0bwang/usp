#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#define R_MODE (S_IRUSR | S_IRGRP | S_IROTH)
#define W_MODE (S_IWUSR | S_IWGRP | S_IWOTH)
#define RW_MODE (R_MODE | W_MODE)

int makepair(char *pipe1, char *pipe2) {
   sigset_t blockmask;
   sigset_t oldmask;
   int returncode = 0;

   if (sigfillset(&blockmask) == -1)
      return -1;
   if (sigprocmask(SIG_SETMASK, &blockmask, &oldmask) == -1)
      return -1;
   if (((mkfifo(pipe1, RW_MODE) == -1) && (errno != EEXIST)) ||
        ((mkfifo(pipe2, RW_MODE) == -1) && (errno != EEXIST))) {
       returncode = errno; 
       unlink(pipe1);
       unlink(pipe2);
   }
   if ((sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) && !returncode)
      returncode = errno;
   if (returncode) {
      errno = returncode; 
      return -1;
   } 
   return 0;
}
