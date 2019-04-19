#include <dirent.h>
#include <errno.h>
#include <stdio.h>
 
int main(int argc, char *argv[]) {
   struct dirent *direntp;
   DIR *dirp;
 
   if (argc != 2) {
      fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
      return 1; 
   }   

   if ((dirp = opendir(argv[1])) == NULL) {
      perror ("Failed to open directory");
      return 1;
   }   

   while ((direntp = readdir(dirp)) != NULL)
      printf("%s\n", direntp->d_name);
   while ((closedir(dirp) == -1) && (errno == EINTR)) ;
   return 0;
}
