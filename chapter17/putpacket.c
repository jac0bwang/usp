#include <stdio.h>
#include <unistd.h>
#include "ntpvm.h"
#include "restart.h"

int putpacket(int fd, int comp_id, int task_id, packet_t type,
               int length, unsigned char *buf) {

   taskpacket_t header;
   int headlen;

   if ( (length < 0) || (length > MAX_PACK_SIZE) )
      return -1;

   headlen = sizeof(taskpacket_t);
   header.compid = comp_id;
   header.taskid = task_id;
   header.type = type;
   header.length = length;

   if (r_write(fd, &header, headlen) != headlen)
      return -1;
   if (r_write(fd, buf, length) != length)
      return -1;
   return 0;
}
