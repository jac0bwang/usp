static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int u_accept(int fd, char *hostn, int hostnsize)
{
   struct sockaddr_in net_client;
   int len = sizeof(struct sockaddr);
   int retval;
   struct hostent *hostptr;

   while ( ((retval =
           accept(fd, (struct sockaddr *)(&net_client), &len)) == -1) &&
          (errno == EINTR) )
      ;  
   if (retval == -1)
      return retval;
   if ( (hostn == NULL) || (hostnsize <= 0) )
      return retval;
   pthread_mutex_lock(&mutex);
   hostptr =
      gethostbyaddr((char *)&(net_client.sin_addr), 4, AF_INET);
   if (hostptr == NULL)
      strncpy(hostn, "unknown",hostnsize-1);
   else
      strncpy(hostn, (*hostptr).h_name,hostnsize-1);
   hostn[hostnsize-1] = 0;
   pthread_mutex_unlock(&mutex);
   return retval;
}
