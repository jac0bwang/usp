#include <stdio.h>
#include <stdlib.h>
void freemakeargv(char **argv);
int makeargv(const char *s, const char *delimiters, char ***argvp);

int main(int argc, char *argv[]) {
   char delim[] = " \t";
   int i;
   char **myargv;
   int numtokens;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s string\n", argv[0]);
      return 1;
   }   
   if ((numtokens = makeargv(argv[1], delim, &myargv)) < 0) {
      fprintf(stderr, "Could not make argument array for %s\n", argv[1]);
      return 1;
   } 
   printf("The argument array contains:\n");
   for (i = 0; i < numtokens; i++)
      printf("[%d]:%s\n", i, myargv[i]);
   freemakeargv(myargv);
   return 0;
}
