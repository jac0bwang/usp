#include <stdio.h>
#include <stdlib.h>
#include "/usr/demo/SOUND/include/multimedia/audio_encode.h"
#define THRESHOLD 20   /* amplitude of ambient room noise, linear PCM */

               /* return 1 if anything in audiobuf is above THRESHOLD */
int hasvoice(char *audiobuf, int length) { 
   int i;

   for (i = 0; i < length; i++)
      if (abs(audio_u2c(audiobuf[i])) > THRESHOLD) 
         return 1;
   return 0;
}
