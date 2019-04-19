CC = cc
COPS =
LINT = lint
LOPS = -x -u
RTLIB = -lrt

all: semfrompath chainsemset monitorshared showshared monitoroneshared msgqueuesave msgqueuein 

semfrompath: semfrompath.c
	$(CC) $(COPS) -o semfrompath semfrompath.c

chainsemset: chainsemset.c setsembuf.c r_semop.c removesem.c restart.c initelement.c
	$(CC) $(COPS) -o chainsemset chainsemset.c setsembuf.c r_semop.c initelement.c removesem.c restart.c

monitorshared: monitorshared.c detachandremove.c restart.c
	$(CC) $(COPS) -o monitorshared monitorshared.c detachandremove.c restart.c

monitoroneshared: monitoroneshared.c restart.c sharedmemsum.c setsembuf.c initelement.c initsemset.c
	$(CC) $(COPS) -o monitoroneshared monitoroneshared.c restart.c sharedmemsum.c setsembuf.c initelement.c initsemset.c $(RTLIB)

showshared: showshared.c sharedmemsum.c setsembuf.c initelement.c initsemset.c
	$(CC) $(COPS) -o showshared showshared.c sharedmemsum.c setsembuf.c initelement.c initsemset.c $(RTLIB)

msgqueuesave: msgqueuesave.c restart.c msgqueuelog.c
	$(CC) $(COPS) -o msgqueuesave msgqueuesave.c restart.c msgqueuelog.c

msgqueuein: msgqueuein.c restart.c msgqueuelog.c
	$(CC) $(COPS) -o msgqueuein msgqueuein.c restart.c msgqueuelog.c

lintall: lintsemfrompath lintchainsemset lintmonitorshared lintmonitoroneshared lintshowshared lintmsgqueuesave lintmsgqueuein lintinitelement

lintsemfrompath:
	$(LINT) $(LOPS) semfrompath.c

lintchainsemset:
	$(LINT) $(LOPS) chainsemset.c setsembuf.c r_semop.c removesem.c initelement.c restart.c

lintmonitorshared:
	$(LINT) $(LOPS) monitorshared.c detachandremove.c restart.c

lintmonitoroneshared:
	$(LINT) $(LOPS) monitoroneshared.c restart.c sharedmemsum.c setsembuf.c

lintshowshared:
	$(LINT) $(LOPS) showshared.c sharedmemsum.c setsembuf.c

lintmsgqueuesave:
	$(LINT) $(LOPS) msgqueuesave.c restart.c msgqueuelog.c

lintmsgqueuein:
	$(LINT) $(LOPS) msgqueuein.c restart.c msgqueuelog.c

lintinitelement:
	$(LINT) $(LOPS) initelement.c

clean:
	rm -f *.o core semfrompath chainsemset monitorshared showshared monitoroneshared msgqueuesave msgqueuein pipe1 pipe2
