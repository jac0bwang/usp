CC = cc
COPS = 
LINT = lint
LOPS = -x -u
RTLIB = -lrt

all: simplealarm blocktest makepairtest blockchild dontblockchild signalterminate passwordtest simplesuspendtest countsignals biff sigjmp asyncio averagesin

asyncio: asyncpollmain asyncsignalmain asyncsignalmainsuspend
 
simplealarm: simplealarm.c
	$(CC) $(COPS) -o simplealarm simplealarm.c

blocktest: blocktest.c
	$(CC) $(COPS) -o blocktest blocktest.c -lm

makepairtest: makepairtest.c makepair.c
	$(CC) $(COPS) -o makepairtest makepairtest.c makepair.c

blockchild: blockchild.c restart.c
	$(CC) $(COPS) -o blockchild blockchild.c restart.c

dontblockchild: dontblockchild.c
	$(CC) $(COPS) -o dontblockchild dontblockchild.c

signalterminate: signalterminate.c
	$(CC) $(COPS) -o signalterminate signalterminate.c -lm

passwordtest: passwordtest.c password.c setecho.c restart.c
	$(CC) $(COPS) -o passwordtest passwordtest.c password.c setecho.c restart.c

simplesuspendtest: simplesuspendtest.c simplesuspend.c
	$(CC) $(COPS) -o simplesuspendtest simplesuspendtest.c simplesuspend.c

biff:	biff.c notifyonoff.c
	$(CC) $(COPS) -o biff biff.c notifyonoff.c

countsignals: countsignals.c
	$(CC) $(COPS) -o countsignals countsignals.c -D_POSIX_PTHREAD_SEMANTICS 

sigjmp: sigjmp.c
	$(CC) $(COPS) -o sigjmp sigjmp.c

averagesin: averagesin.c
	$(CC) $(COPS) -o averagesin averagesin.c -lm

asyncpollmain: asyncpollmain.c asyncmonitorpoll.c asyncmonitorpollstuff.c
	$(CC) $(COPS) -o asyncpollmain asyncpollmain.c asyncmonitorpoll.c asyncmonitorpollstuff.c $(RTLIB)

asyncsignalmain: asyncsignalmain.c asyncmonitorsignal.c asyncmonitorpollstuff.c restart.c
	$(CC) $(COPS) -o asyncsignalmain asyncsignalmain.c asyncmonitorsignal.c asyncmonitorpollstuff.c restart.c $(RTLIB)

asyncsignalmainsuspend: asyncsignalmainsuspend.c asyncmonitorsignal.c restart.c
	$(CC) $(COPS) -o asyncsignalmainsuspend asyncsignalmainsuspend.c asyncmonitorsignal.c restart.c $(RTLIB)

lintall: lintsimplealarm lintblocktest lintmakepair lintblockchild lintsignalterminate lintpasswordtest lintpasswordtest lintsigsuspend1 lintsigsuspend2 lintsigsuspend3 lintsimplesuspend lintcountsignals lintsigjmp lintbiff lintaveragesin lintasyncpollmain lintasyncsignalmain lintasyncsignalmainsuspend lintasyncmonitorsignal linttestignored

lintsimplealarm:
	$(LINT) $(LOPS) simplealarm.c

lintblocktest:
	$(LINT) $(LOPS) blocktest.c -lm

lintmakepair:
	$(LINT) $(LOPS) makepairtest.c makepair.c

lintblockchild:
	$(LINT) $(LOPS) blockchild.c restart.c

lintsignalterminate:
	$(LINT) $(LOPS) signalterminate.c -lm

lintpasswordtest:
	$(LINT) $(LOPS) passwordtest.c password.c setecho.c restart.c 

lintsigsuspend1:
	$(LINT) $(LOPS) sigsuspendtest1.c

lintsigsuspend2:
	$(LINT) $(LOPS) sigsuspendtest2.c

lintsigsuspend3:
	$(LINT) $(LOPS) sigsuspendtest3.c

lintsimplesuspend:
	$(LINT) $(LOPS) simplesuspendtest.c simplesuspend.c

lintcountsignals:
	$(LINT) $(LOPS) countsignals.c -D_POSIX_PTHREAD_SEMANTICS

lintsigjmp:
	$(LINT) $(LOPS) sigjmp.c

lintbiff:
	$(LINT) $(LOPS) biff.c notifyonoff.c

lintaveragesin:
	$(LINT) $(LOPS) averagesin.c -lm

lintasyncpollmain:
	$(LINT) $(LOPS) asyncpollmain.c asyncmonitorpoll.c asyncmonitorpollstuff.c $(RTLIB)

lintasyncsignalmain:
	$(LINT) $(LOPS) asyncsignalmain.c asyncmonitorsignal.c asyncmonitorpollstuff.c restart.c $(RTLIB)

lintasyncsignalmainsuspend:
	$(LINT) $(LOPS) asyncsignalmainsuspend.c asyncmonitorsignal.c restart.c $(RTLIB)

lintasyncmonitorsignal:
	$(LINT) $(LOPS) asyncmonitorsignal.c $(RTLIB)

linttestignored:
	$(LINT) $(LOPS) testignored.c

clean:
	rm -f *.o core simplealarm blocktest makepairtest blockchild dontblockchild signalterminate passwordtest biff simplesuspendtest asyncpollmain sigjmp countsignals asyncsignalmainsuspend asyncsignalmain averagesin pipe1 pipe2
