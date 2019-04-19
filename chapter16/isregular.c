#include <sys/stat.h>
#include <sys/types.h>

int isregular(const char *filename) {
   struct stat buf;

   if (lstat(filename, &buf) == -1)
      return 0;
   return S_ISREG(buf.st_mode);
}
