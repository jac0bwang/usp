#define GETHOST_BUFSIZE 8192

int u_accept(int fd, char *hostn, int hostnsize)
{
   struct sockaddr_in net_client;
   int len = sizeof(struct sockaddr);
   int retval;
   struct hostent result;
   struct hostent *hostptr;
   int h_error;
   char buf[GETHOST_BUFSIZE];

   while ( ((retval =
           accept(fd, (struct sockaddr *)(&net_client), &len)) == -1) &&
          (errno == EINTR) )
      ;  
   if (retval == -1)
      return retval;
   if ( (hostn == NULL) || (hostnsize <= 0) )
      return retval;
   hostptr =
      gethostbyaddr_r((char *)&(net_client.sin_addr), 4, AF_INET,
         &result, buf, GETHOST_BUFSIZE, &h_error);
   if (hostptr == NULL)
      strncpy(hostn, "unknown",hostnsize-1);
   else
      strncpy(hostn, (*hostptr).h_name,hostnsize-1);
   hostn[hostnsize-1] = 0;
   return retval;
}
