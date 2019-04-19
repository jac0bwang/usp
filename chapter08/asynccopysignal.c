#include <aio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stropts.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
 
#define BLKSIZE 1024
 
static struct aiocb aiocb1;
static struct aiocb aiocb2;
static volatile char buf1[BLKSIZE];
static int fd1 = 0;
static int fd1error = 0;
static int fd2 = 0;
static int fd2error = 0;

#include "asynccopysignalhandler.c"
 
int main(int argc, char *argv[]) {
   sigset_t omask;
   struct sigaction newact;
                                       /* open the file descriptors for I/O */
   if (argc != 3) {
      fprintf(stderr, "Usage: %s filename1 filename2\n", argv[0]);
      return 1; 
   }
   if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
      fprintf(stderr,"Could not open %s: %s\n", argv[1], strerror(errno));
      return 1; 
   }
   if ((fd2 = open(argv[2], O_WRONLY)) == -1) {
      fprintf(stderr,"Could not open %s: %s\n", argv[2], strerror(errno));
      return 1;
   }
                             /* Set up handlers for SIGRTMAX and SIGRTMAX-1 */
fprintf(stderr,"Opens complete\n");
   if ((sigemptyset(&newact.sa_mask) == -1) ||
       (sigaddset(&newact.sa_mask, SIGRTMAX) == -1) ||
       (sigaddset(&newact.sa_mask, SIGRTMAX-1) == -1) ||
       (sigprocmask(SIG_BLOCK, &newact.sa_mask, &omask) == -1) ) {
       perror("Could not block SIGRTMAX or SIGRTMAX-1");
       return 1; 
   }
   newact.sa_sigaction = aiohandler;
   newact.sa_flags = SA_SIGINFO;
   if ((sigaction(SIGRTMAX, &newact, NULL) == -1) ||
       (sigaction(SIGRTMAX-1, &newact, NULL) == -1) ||
       (sigprocmask(SIG_UNBLOCK, &newact.sa_mask, NULL) == -1)) {
      perror("Could not unblock SIGRTMAX or SIGRTMAX-1");
      return 1; 
   }
   aiocb1.aio_fildes = fd1;             /* Start first I/O operation on fd1 */
   aiocb1.aio_offset = 0;
   aiocb1.aio_buf = (void *)buf1;
   aiocb1.aio_nbytes = BLKSIZE;
   aiocb1.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   aiocb1.aio_sigevent.sigev_signo = SIGRTMAX;
   aiocb1.aio_sigevent.sigev_value.sival_ptr = &aiocb1;
   aiocb2.aio_fildes = fd2;             /* Start first I/O operation on fd2 */
   aiocb2.aio_offset = 0;
   aiocb2.aio_buf = (void *)buf1;
   aiocb2.aio_nbytes = 5;
   aiocb2.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   aiocb2.aio_sigevent.sigev_signo = SIGRTMAX-1;
   aiocb2.aio_sigevent.sigev_value.sival_ptr = &aiocb2;
   fd1error = aio_read(&aiocb1);
   if (fd1error == -1) {
       perror("The aio_read failed");
       return 1; 
   }
   while(!fd1error || !fd2error)                /* overlapping computations */

      ;                                                      /* do whatever */
   return 0; 
}
