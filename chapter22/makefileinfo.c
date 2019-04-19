#include <fcntl.h>
#include <ftw.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#define MAXPATH 100
#define NUMRANGES 5

typedef struct {
   off_t filesize;
   char path[MAXPATH+1];
} fileinfo;

static int filecounts[NUMRANGES];
static fileinfo *files[NUMRANGES];
static int maxnum;

static int whichlist(off_t size) {
   int base = 10;
   int limit;
   int lnum;

   if (size < base)
      return -1;
   for (lnum = 0, limit = base*base;
        lnum < NUMRANGES - 1;
        lnum++, limit *= 10)
      if (size < limit)
         break;
   return lnum;
}

static int insertfile(const char *path, const struct stat *statbuf, 
           int info, struct FTW *ftwinfo) {
   int fd;
   int lnum;
   static int numfull = 0;

   if (info != FTW_F) 
      return 0;
   if (strlen(path) > MAXPATH)
      return 0;
   if ((statbuf->st_mode & S_IFREG) == 0)
      return 0;
   if ((fd = open(path, O_RDONLY | O_NONBLOCK)) == -1)
      return 0;
   if (r_close(fd) == -1)
      return 0;
   lnum = whichlist(statbuf->st_size);
   if (lnum < 0)
      return 0;
   if (filecounts[lnum] == maxnum)
      return 0;
   strcpy(files[lnum][filecounts[lnum]].path, path);
   files[lnum][filecounts[lnum]].filesize = statbuf->st_size;
   filecounts[lnum]++;
   if (filecounts[lnum] == maxnum) numfull++;
   if (numfull == NUMRANGES)
      return 1;
   return 0;
}

void showfiles(int which) {
   int i;
   fprintf(stderr, "List %d contains %d entries\n", which, filecounts[which]);
   for (i = 0; i < filecounts[which]; i++) 
      fprintf(stderr, "%*d: %s\n",which + 6,files[which][i].filesize,
                      files[which][i].path);
}

int main(int argc, char *argv[]) {
   int depth = 10;
   int ftwflags = FTW_PHYS;
   int i;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s directory maxnum\n", argv[0]);
      return 1;
   }
   maxnum = atoi(argv[2]);
   for (i = 0; i < NUMRANGES; i++) {
      filecounts[i] = 0;
      files[i] = (fileinfo *)calloc(maxnum, sizeof(fileinfo));
      if (files[i] == NULL) {
         fprintf(stderr,"Failed to allocate memory for list %d\n", i);
         return 1;
      }
   }
   fprintf(stderr, "Max number for each range is %d\n", maxnum);
   if (nftw(argv[1], insertfile, depth, ftwflags) == -1) {
      perror("Failed to execute nftw");
      return 1;
   }
   fprintf(stderr, "**** nftw is done\n");
   fprintf(stderr, "Counts are as follows with sizes at most %d\n", maxnum);
   for (i = 0; i < NUMRANGES; i++)
      fprintf(stderr, "%d:%d\n", i, filecounts[i]);
   for (i = 0; i < NUMRANGES; i++)
      showfiles(i);
   return 0;
}
