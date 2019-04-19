#include <stdio.h>

int makepair(char *pipe1, char *pipe2);

int main(int argc, char *argv[]) {
   int error;

   if (argc != 3) {
      fprintf(stderr,"Usage: %s pipe1 pipe2\n",argv[0]);
      return 1;
   }
   error = makepair(argv[1], argv[2]);
   if (error)
      perror("makepair error");
   else
      fprintf(stderr,"makepair returned %d\n",error);
   return 0;
}
   
