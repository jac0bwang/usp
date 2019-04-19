#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int isregular(const char *filename);

int main(void) {
   struct dirent *direntp;
   DIR *dirp;

   if ((dirp = opendir(".")) == NULL) {
      perror ("failed to open directory");
      return 1;
   }
   while ( (direntp = readdir(dirp)) != NULL )
      if (isregular(direntp->d_name)) 
         printf("    regular %s\n", direntp->d_name);
      else
         printf("not regular %s\n", direntp->d_name);
   closedir(dirp);
   return 0;
}
