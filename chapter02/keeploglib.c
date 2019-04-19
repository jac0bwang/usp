#include <stdio.h>
#include <stdlib.h>
#include "listlib.h"

int runproc(char *cmd) { /* execute cmd; store cmd and time in history list */
   data_t execute;

   if (time(&(execute.time)) == -1)
      return -1;
   execute.string = cmd;
   if (system(cmd) == -1)           /* command could not be executed at all */
      return -1;
   return adddata(execute);
}

void showhistory(FILE *f) {        /* output the history list of the file f */
   data_t data;
   int key;

   key = accessdata();
   if (key == -1) {
      fprintf(f, "No history\n");
      return;
   }
   while (!getdata(key, &data) && (data.string != NULL)) {
      fprintf(f, "Command: %s\nTime: %s\n", data.string, ctime(&(data.time)));
      free(data.string);
   }
}
