int fd[2];
pid_t haschild;
 
pipe(fd);                                                   /* pipe a */
dup2(fd[0], STDIN_FILENO);
dup2(fd[1], STDOUT_FILENO);
close(fd[0]);
close(fd[1]);
pipe(fd);                                                   /* pipe b */
haschild = fork();
if (haschild > 0)
   dup2(fd[1], STDOUT_FILENO);      /* parent(A) redirects std output */
else if (!haschild)
   dup2(fd[0], STDIN_FILENO);         /* child(B) redirects std input */
close(fd[0]);  
close(fd[1]);
