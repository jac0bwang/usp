#include <stdio.h>
#include <stdlib.h>
#include "audiolib.h"
 
#define BUFSIZE 1024
int main (void) {
   char buffer[BUFSIZE];
   int bytesread;
 
   if (open_audio() == -1) {
      perror("Failed to open audio");
      return 1; 
   }
   for( ; ; ) {
      if ((bytesread = read_audio(buffer, BUFSIZE)) == -1) {
          perror("Failed to read microphone");
          break;
      } else if (write_audio(buffer, bytesread) == -1) {
          perror("Failed to write to speaker");
          break;
      } 
   }  
   close_audio();
   return 1;
}
