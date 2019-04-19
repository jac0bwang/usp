CC = cc
COPS =
LINT = lint
LOPS = -x -u
NETLIBS = -lsocket -lnsl

all: a2ts testpacket ts2a ts2log

a2ts: a2ts.c ntpvm.h restart.c
	$(CC) $(COPS) -o a2ts a2ts.c  restart.c

ts2a: ts2a.c ntpvm.h
	$(CC) $(COPS) -o ts2a ts2a.c 

ts2log: ts2log.c ntpvm.h restart.c uici.c uiciname.c rlogging.c
	$(CC) $(COPS) -o ts2log ts2log.c restart.c uici.c uiciname.c rlogging.c $(NETLIBS)

testpacket: testpacket.c getpacket.c putpacket.c restart.c ntpvm.h
	$(CC) $(COPS) -o testpacket testpacket.c getpacket.c putpacket.c restart.c

lintall: linta2ts lintts2a lintts2log linttestpacket

linta2ts:
	$(LINT) $(LOPS) a2ts.c

lintts2a:
	$(LINT) $(LOPS) ts2a.c

lintts2log:
	$(LINT) $(LOPS) ts2log.c restart.c uici.c rlogging.c

linttestpacket:
	$(LINT) $(LOPS) testpacket.c getpacket.c putpacket.c restart.c

clean:
	rm -f *.o core a2ts ts2a testpacket ts2log
