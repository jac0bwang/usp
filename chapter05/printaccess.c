#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

void printaccess(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      perror("Failed to get file status");
   else
      printf("%s last accessed at %s", path, ctime(&statbuf.st_atime));
}
