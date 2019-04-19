#include <string.h>
#define LINE_DELIMITERS "\n"
#define WORD_DELIMITERS " " 

static int wordcount(char *s) {
   int count = 1;

   if (strtok(s, WORD_DELIMITERS) == NULL)
      return 0;
   while (strtok(NULL, WORD_DELIMITERS) != NULL)
      count++;
   return count;
}

double wordaverage(char *s) {      /* return average size of words in s */
   int linecount = 1;
   char *nextline;
   int words;

   nextline = strtok(s, LINE_DELIMITERS);
   if (nextline == NULL)
      return 0.0;
   words = wordcount(nextline);
   while ((nextline = strtok(NULL, LINE_DELIMITERS)) != NULL) {
      words += wordcount(nextline);
      linecount++;
   }
   return (double)words/linecount;
}
