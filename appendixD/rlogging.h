#define LFILE_GENLENGTH 16
typedef struct LFILE {
   int id;
   int fd;
   int tmode;
   char gen[LFILE_GENLENGTH];
} LFILE;

LFILE *lopen(char *host, int port);
int lclose(LFILE *mf);                    /* not thread safe */
void ldebug(int debug);
int lprintf(LFILE *mf, char *fmt, ...);
int lprintfg(LFILE *mf, char *gen, char *fmt, ...);
int lgenerator(LFILE *mf, char *gen);
int lsendtime(LFILE *mf);

