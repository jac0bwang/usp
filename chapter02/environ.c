#include <stdio.h>

extern char **environ; 

int main(void) {
   int i;

   printf("The environment list follows:\n");
   for(i = 0; environ[i] != NULL; i++)
     printf("environ[%d]: %s\n", i, environ[i]);
   return 0;
}
