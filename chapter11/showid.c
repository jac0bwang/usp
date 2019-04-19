#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

   if (argc != 2) {
      fprintf(stderr,"Usage: %s string \n",argv[0]);
      return 1;
   }

   fprintf(stderr,"%s: pid=%5d pgid=%5d psid=%5d ppid=%5d\n",
         argv[1],(int)getpid(),(int)getpgrp(),(int)getsid(0),(int)getppid());
   return 0;
}
