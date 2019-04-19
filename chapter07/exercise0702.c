int i, myint;

for (i = 0; i < 10; i++) {
   write(STDOUT_FILENO, &i, sizeof(i));
   read(STDIN_FILENO, &myint, sizeof(myint));
   fprintf(stderr, "%d\n", myint);
}
