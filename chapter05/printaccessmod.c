#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#define CTIME_SIZE 26

void printaccessmod(char *path) {
   char atime[CTIME_SIZE];   /* 26 is the size of the ctime string */
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      perror("Failed to get file status");
   else {
      strncpy(atime, ctime(&statbuf.st_atime), CTIME_SIZE - 1);
      atime[CTIME_SIZE - 2] = 0;
      printf("%s accessed: %s modified: %s", path, atime,
               ctime(&statbuf.st_mtime));
   }
}
