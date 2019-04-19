#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

void printaccessmodbad(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      perror("Failed to get file status");
   else
      printf("%s accessed: %s modified: %s", path,
             ctime(&statbuf.st_atime), ctime(&statbuf.st_mtime));
}
