#include <dirent.h>
#include <errno.h>
#include <stdio.h>

void printaccessmod(char *path);
 
int main(int argc, char *argv[]) {
   struct dirent *direntp;
   DIR *dirp;
 
   if (argc != 2) {
      fprintf(stderr,"Usage: %s directory_name\n", argv[0]);
      return 1; 
   }   
 
   if ((dirp = opendir(argv[1])) == NULL) {
      perror ("failed to open directory");
      return 1;
   }   
   while ( (direntp = readdir(dirp)) != NULL )
      printaccessmod(direntp->d_name);
 
   while ( (closedir(dirp) == -1) && (errno == EINTR))  ;
   return 0;
}
