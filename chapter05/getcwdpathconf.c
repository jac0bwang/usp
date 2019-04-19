#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void) {
   long maxpath;
   char *mycwdp;

   if ((maxpath = pathconf(".", _PC_PATH_MAX)) == -1) {
      perror("Failed to determine the pathname length");
      return 1;
   }
   if ((mycwdp = (char *) malloc(maxpath)) == NULL) {
      perror("Failed to allocate space for pathname");
      return 1;
   } 
   if (getcwd(mycwdp, maxpath) == NULL) {
      perror("Failed to get current working directory");
      return 1;
   }
   printf("Current working directory: %s\n", mycwdp);
   return 0;
}
