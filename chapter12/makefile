CC = cc
COPS =
LINT = lint
LOPS = -x -u
LIBTHREAD = -lpthread

all: monitorfdtest detachfuntest monitorfdcanceltest callcopymalloc callcopypass copymultiple badparameters makeprioritytest

monitorfdtest: monitorfdtest.c monitorfd.c processfd.c restart.c
	$(CC) $(COPS) -o monitorfdtest monitorfdtest.c monitorfd.c processfd.c restart.c $(LIBTHREAD)

monitorfdcanceltest: monitorfdcanceltest.c monitorfdcancel.c processfdcancel.c restart.c 
	$(CC) $(COPS) -o monitorfdcanceltest monitorfdcanceltest.c monitorfdcancel.c processfdcancel.c restart.c $(LIBTHREAD)

detachfuntest: detachfuntest.c detachfun.c
	$(CC) $(COPS) -o detachfuntest detachfuntest.c detachfun.c $(LIBTHREAD)

callcopymalloc: callcopymalloc.c copyfilemalloc.c restart.c
	$(CC) $(COPS) -o callcopymalloc callcopymalloc.c copyfilemalloc.c restart.c $(LIBTHREAD)

callcopypass: callcopypass.c copyfilepass.c restart.c
	$(CC) $(COPS) -o callcopypass callcopypass.c copyfilepass.c restart.c $(LIBTHREAD)

copymultiple: copymultiple.c copyfilepass.c restart.c
	$(CC) $(COPS) -o copymultiple copymultiple.c copyfilepass.c restart.c $(LIBTHREAD)

badparameters: badparameters.c
	$(CC) $(COPS) -o badparameters badparameters.c $(LIBTHREAD)

makeprioritytest: makeprioritytest.c
	$(CC) $(COPS) -o makeprioritytest makeprioritytest.c makepriority.c $(LIBTHREAD)

lintall: lintmonitorfd lintmonitorfdcancel lintdetachfun lintcallcopymalloc lintcallcopypass lintcopymultiple lintbadparameters lintwhichexit lintmakepriority

lintmonitorfd:
	$(LINT) $(LOPS) monitorfd.c processfd.c restart.c 

lintmonitorfdcancel:
	$(LINT) $(LOPS) monitorfdcanceltest.c monitorfdcancel.c processfdcancel.c restart.c 

lintdetachfun:
	$(LINT) $(LOPS) detachfuntest.c detachfun.c

lintcallcopymalloc:
	$(LINT) $(LOPS) callcopymalloc.c copyfilemalloc.c restart.c

lintcallcopypass:
	$(LINT) $(LOPS) callcopypass.c copyfilepass.c restart.c

lintcopymultiple:
	$(LINT) $(LOPS) copymultiple.c copyfilepass.c restart.c

lintbadparameters:
	$(LINT) $(LOPS) badparameters.c

lintwhichexit:
	$(LINT) $(LOPS) whichexit.c

lintmakepriority:
	$(LINT) $(LOPS) makeprioritytest.c makepriority.c

clean:
	rm -f *.o core pipe1 pipe2 monitorfdtest detachfuntest monitorfdcanceltest copymultiple callcopymalloc callcopypass badparameters makeprioritytest
