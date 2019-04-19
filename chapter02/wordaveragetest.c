#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 10240

double wordaverage(char *s);

int main() {
   char buf[BUFSIZE];
   int size;
   double ave;
   int num;

   size = read(0,buf,BUFSIZE-1);
   if (size <= 0) {
      fprintf(stderr,"Error reading from standard input\n");
      return 1;
   }
   while (size < BUFSIZE-1) {
      num = read(0,buf+size,BUFSIZE-size-1);
      fprintf(stderr,"%d bytes read\n",num);
      if (num == 0) break;
      if (num < 0) {
         fprintf(stderr,"Error reading from standard input!\n");
         return 1;
      }
      size += num;
   }
   buf[size] = 0;
   fprintf(stderr,"Total number of bytes read = %d\n",size);
   ave = wordaverage(buf);
   fprintf(stderr,"The average number of words is %f\n",ave);
   return 0;
}
   

   
