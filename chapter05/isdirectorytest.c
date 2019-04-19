#include <stdio.h>

int isdirectory(char *path);

int main(int argc, char *argv[]) {

   if (argc != 2) {
      fprintf(stderr,"Usage: %s filename\n",argv[0]);
      return 1;
   }

   if (isdirectory(argv[1]))
      fprintf(stderr,"%s is a directory\n",argv[1]);
   else
      fprintf(stderr,"%s is not a directory\n",argv[1]);
   return 0;
}
