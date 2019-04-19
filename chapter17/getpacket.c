#include <stdio.h>
#include <unistd.h>
#include "ntpvm.h"
#include "restart.h"

int getpacket(int fd, int *comp_idp, int *task_idp, packet_t *typep,
               int *lengthp, unsigned char *buf) {

   taskpacket_t header;
   int headlen;

   headlen = sizeof(taskpacket_t);

   if (readblock(fd, &header, headlen) != headlen)
      return -1;
   if ( (header.length < 0) || (header.length > MAX_PACK_SIZE) )
      return -1;
   if (readblock(fd, buf, header.length) != header.length)
      return -1;
   *comp_idp = header.compid;
   *task_idp = header.taskid;
   *typep = header.type;
   *lengthp = header.length;
   return 0;
}
