#include <stdio.h>

char **getpaths(void);

int main(void) {
   char **paths;
   int i;

   paths = getpaths();
   if (paths == NULL) {
      fprintf(stderr,"No path variable\n");
      return 1;
   }
   
   for (i = 0; paths[i] != NULL; i++)
      printf("[%d]:%s\n", i, paths[i]);
   return 0;
}
