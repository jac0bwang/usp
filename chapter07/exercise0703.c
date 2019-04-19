int i, myint; 
 
for (i = 0; i < 10; i++) { 
   read(STDIN_FILENO, &myint, sizeof(myint));
   write(STDOUT_FILENO, &i, sizeof(i));
   fprintf(stderr, "%d\n", myint);
} 
