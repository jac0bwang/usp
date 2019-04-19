#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stropts.h>
#include <unistd.h>
#include <sys/audio.h>
#include "restart.h"
#define AUDIO "/dev/audio"
 
static int audio_fd = -1;   /* audio device file descriptor */
 
int open_audio(void) {
   while (((audio_fd = open(AUDIO, O_RDWR)) == -1) && (errno == EINTR)) ; 
   if (audio_fd == -1)
      return -1;    
   return 0;
}
 
void close_audio(void) {
   r_close(audio_fd);
   audio_fd = -1;
}
         
int read_audio(char *buffer, int maxcnt) {
   return r_read(audio_fd, buffer, maxcnt);
}     
 
int write_audio(char *buffer, int maxcnt) {
   return r_write(audio_fd, buffer, maxcnt);
}      

int get_record_buffer_size(void) {
   audio_info_t myaudio;
   if (audio_fd == -1) 
      return -1;
   if (ioctl(audio_fd, AUDIO_GETINFO, &myaudio) == -1)
      return -1;
   else
      return myaudio.record.buffer_size;
}
