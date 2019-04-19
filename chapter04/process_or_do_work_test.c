#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void process_or_do_work(int fd1, int fd2);
int setnonblock(int fd);

void docommand(char *buf, int num) {
   fprintf(stderr,"Got command !%.*s!\n",num,buf);
}

void dosomething(void) {
   fprintf(stderr,"There is nothing to do\n");
   sleep(5);
}

void processcommand(char *buf, int num) {
   fprintf(stderr,"Got command !%.*s!\n",num,buf);
}

int main(void) {
   int fd;

   fd = open("pipe1",O_RDONLY|O_NONBLOCK);
   if (fd < 0) {
      fprintf(stderr,"Could not open mypipe for nonblocking input\n");
      return 1;
   }
   setnonblock(STDIN_FILENO);
   process_or_do_work(STDIN_FILENO,fd);
   return 0;
}
