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

void suspenduntilready(struct aiocb *aiocb1, struct aiocb *aiocb2);

static void process_buffer(char *buf, int bufsize) {
   write(STDERR_FILENO,buf,bufsize);
}

static void process_buffer_1(char *buf, int bufsize) {
   fprintf(stderr,"Got %d bytes from buffer 1\n",bufsize);
   process_buffer(buf,bufsize);
}

static void process_buffer_2(char *buf, int bufsize) {
   fprintf(stderr,"Got %d bytes from buffer 2\n",bufsize);
   process_buffer(buf,bufsize);
}
 
int main(int argc, char *argv[]) {
   struct aiocb aiocb1;
   struct aiocb aiocb2;
   volatile char buf2[BLKSIZE];
   volatile char buf1[BLKSIZE];
   int fd1 = 0;
   int fd2 = 0;
   int myerror1 = 0;
   int myerror2 = 0;
   int done1 = 0;
   int done2 = 0;
   int numbytes;
                                 /* open the file descriptors for I/O */
   if (argc != 3) {
      fprintf(stderr, "Usage: %s filename1 filename2\n", argv[0]);
      return 1; 
   }
   if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
      fprintf(stderr,"Could not open %s: %s\n", argv[1], strerror(errno));
      return 1; 
   }
   if ((fd2 = open(argv[2], O_RDONLY)) == -1) {
      fprintf(stderr,"Could not open %s: %s\n", argv[2], strerror(errno));
      return 1;
   }
   aiocb1.aio_fildes = fd1;         /* Start first I/O operation on fd1 */
   aiocb1.aio_offset = 0;
   aiocb1.aio_buf = (void *)buf1;
   aiocb1.aio_nbytes = BLKSIZE;
   aiocb1.aio_sigevent.sigev_notify = SIGEV_NONE;
   if (aio_read(&aiocb1))
      perror("initiate read error on first file");
   aiocb2.aio_fildes = fd2;     /* Start first I/O operation on fd2 */
   aiocb2.aio_offset = 0;
   aiocb2.aio_buf = (void *)buf2;
   aiocb2.aio_nbytes = BLKSIZE;
   aiocb2.aio_sigevent.sigev_notify = SIGEV_NONE;
   if (aio_read(&aiocb2))
      perror("initiate read error on second file");
   for ( ; ;) {
      if (done1 && done2)
         break;
      if (done1)
         suspenduntilready(NULL, &aiocb2);
      else if (done2)
         suspenduntilready(&aiocb1, NULL);
      else
         suspenduntilready(&aiocb1, &aiocb2);
      if (!done1) {
         myerror1 = aio_error(&aiocb1);
         if (myerror1 != EINPROGRESS) {
            if (myerror1) {
               perror("read error on first file\n");
               done1 = 1;
            }
            else {
               numbytes = aio_return(&aiocb1);
               if (numbytes == 0)
                  done1 = 1;
               else {
                  process_buffer_1((char *)aiocb1.aio_buf,numbytes);
                  if (myerror1 = aio_read(&aiocb1)) {
                     perror("initiate read error on first file");
                     done1 = 1;
                  }
               }
            }
         }
      }
      if (!done2) {
         myerror2 = aio_error(&aiocb2);
         if (myerror2 != EINPROGRESS) {
            if (myerror2) {
               perror("read error on second file\n");
               done2 = 1;
            }
            else {
               numbytes = aio_return(&aiocb2);
               if (numbytes == 0)
                  done2 = 1;
               else {
                  process_buffer_2((char *)aiocb2.aio_buf,numbytes);
                  if (myerror2 = aio_read(&aiocb2)) {
                     perror("initiate read error on second file");
                     done2 = 1;
                  }
               }
            }
         }
      }
   }
}
