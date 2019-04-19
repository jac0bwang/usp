#include <unistd.h>
#include "ntpvm.h"
 
int getpacket(int, int *, int *, packet_t *, int *, unsigned char *);
int putpacket(int, int, int, packet_t, int, unsigned char *);
 
int main(void) {
   unsigned char buf[MAX_PACK_SIZE];
   int compid;
   int taskid;
   int tdatalen;
   int tin, tout;
   packet_t type;
 
   tin = STDIN_FILENO;
   tout = STDOUT_FILENO;
   while (getpacket(tin, &compid, &taskid, &type, &tdatalen, buf) != -1) {
      if (putpacket(tout, compid, taskid, type, tdatalen, buf) == -1)
         break;
   }
   return 0;
}
