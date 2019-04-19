/* uiciname.c  name resolution functions */

#include <ctype.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "uiciname.h"

#ifndef REENTRANCY
#define REENTRANCY REENTRANT_NONE
#endif

#if REENTRANCY==REENTRANT_MUTEX
#include <pthread.h>
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#if REENTRANCY==REENTRANT_NONE
/* Convert struct in_addr to a host name */
void addr2name(struct in_addr addr, char *name, int namelen) {
   struct hostent *hostptr;
   hostptr = gethostbyaddr((char *)&addr, 4, AF_INET);
   if (hostptr == NULL)
      strncpy(name, inet_ntoa(addr), namelen-1);
   else
      strncpy(name, hostptr->h_name, namelen-1);
   name[namelen-1] = 0;
}

/* Return -1 on error, 0 on success */
int name2addr(char *name, in_addr_t *addrp) {
   struct hostent *hp;

   if (isdigit((int)(*name)))
      *addrp = inet_addr(name);
   else {
      hp = gethostbyname(name);
      if (hp == NULL)
         return -1;
      memcpy((char *)addrp, hp->h_addr_list[0], hp->h_length);
   }
   return 0;
}
#elif REENTRANCY==REENTRANT_R
#define GETHOST_BUFSIZE 8192
void addr2name(struct in_addr addr, char *name, int namelen) {
   char buf[GETHOST_BUFSIZE];
   int h_error;
   struct hostent *hp;
   struct hostent result;

   hp = gethostbyaddr_r((char *)&addr, 4, AF_INET, &result, buf,
                         GETHOST_BUFSIZE, &h_error);
   if (hp == NULL)
      strncpy(name, inet_ntoa(addr), namelen-1);
   else
      strncpy(name, hp->h_name, namelen-1);
   name[namelen-1] = 0;
}
 
/* Return -1 on error, 0 on success */
int name2addr(char *name, in_addr_t *addrp) {
   char buf[GETHOST_BUFSIZE];
   int h_error;
   struct hostent *hp;
   struct hostent result;
 
   if (isdigit((int)(*name)))
      *addrp = inet_addr(name);
   else {
      hp = gethostbyname_r(name, &result, buf, GETHOST_BUFSIZE, &h_error);
      if (hp == NULL)
         return -1;
      memcpy((char *)addrp, hp->h_addr_list[0], hp->h_length);
   }
   return 0;
}   
#elif REENTRANCY==REENTRANT_MUTEX
/* Convert struct in_addr to a host name */
void addr2name(struct in_addr addr, char *name, int namelen) {
   struct hostent *hostptr;

   if (pthread_mutex_lock(&mutex) == -1) {
      strncpy(name, inet_ntoa(addr), namelen-1); 
      name[namelen-1] = 0;
      return;
   }
   hostptr = gethostbyaddr((char *)&addr, 4, AF_INET);
   if (hostptr == NULL)
      strncpy(name, inet_ntoa(addr), namelen-1); 
   else  
      strncpy(name, hostptr->h_name, namelen-1);
   pthread_mutex_unlock(&mutex);
   name[namelen-1] = 0;
}
 
/* Return -1 on error, 0 on success */
int name2addr(char *name, in_addr_t *addrp) {
   struct hostent *hp;
 
   if (isdigit((int)(*name)))
      *addrp = inet_addr(name);
   else {
      if (pthread_mutex_lock(&mutex) == -1)
         return -1;
      hp = gethostbyname(name);
      if (hp == NULL) {
         pthread_mutex_unlock(&mutex);
         return -1;
      }
      memcpy((char *)addrp, hp->h_addr_list[0], hp->h_length);
      pthread_mutex_unlock(&mutex);
   }
   return 0;
}
#elif REENTRANCY==REENTRANT_POSIX
/* Convert struct in_addr to a host name */
void addr2name(struct in_addr addr, char *name, int namelen) {
   struct sockaddr_in saddr;
   saddr.sin_family = AF_INET;
   saddr.sin_port = 0;
   saddr.sin_addr = addr;
   if (getnameinfo((struct sockaddr *)&saddr, sizeof(saddr), name, namelen,
         NULL, 0, 0) != 0) {
      strncpy(name, inet_ntoa(addr), namelen-1);
      name[namelen-1] = 0;
   }
}

/* Return -1 on error, 0 on success */
int name2addr(char *name, in_addr_t *addrp) {
   struct addrinfo hints;
   struct addrinfo *res;
   struct sockaddr_in *saddrp;

   hints.ai_flags = AI_PASSIVE;
   hints.ai_family = PF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = 0;
   hints.ai_addrlen = 0;
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;
 
   if (getaddrinfo(name, NULL, &hints, &res) != 0)
      return -1;
   saddrp = (struct sockaddr_in *)(res->ai_addr);
   memcpy(addrp, &saddrp->sin_addr.s_addr, 4);
   freeaddrinfo(res);
   return 0;
}

#endif
