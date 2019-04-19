CC = cc
COPS =
LOPS = -x -u
LINT = lint

all: outputPID outputIDs simplefork twoprocs badprocessID simplechain simplefan fanwait fanwaitmsg parentwaitpid chainwaitmsg execls execcmd execcmdargv runback showreturnstatustest

outputPID: outputPID.c
	$(CC) $(COPS) -o outputPID outputPID.c

outputIDs: outputIDs.c
	$(CC) $(COPS) -o outputIDs outputIDs.c

simplefork: simplefork.c
	$(CC) $(COPS) -o simplefork simplefork.c

twoprocs: twoprocs.c
	$(CC) $(COPS) -o twoprocs twoprocs.c

badprocessID: badprocessID.c
	$(CC) $(COPS) -o badprocessID badprocessID.c

simplechain: simplechain.c
	$(CC) $(COPS) -o simplechain simplechain.c

simplefan: simplefan.c
	$(CC) $(COPS) -o simplefan simplefan.c

fanwait: fanwait.c r_wait.c
	$(CC) $(COPS) -o fanwait fanwait.c r_wait.c

fanwaitmsg: fanwaitmsg.c
	$(CC) $(COPS) -o fanwaitmsg fanwaitmsg.c

parentwaitpid: parentwaitpid.c
	$(CC) $(COPS) -o parentwaitpid parentwaitpid.c

chainwaitmsg: chainwaitmsg.c
	$(CC) $(COPS) -o chainwaitmsg chainwaitmsg.c

execls: execls.c
	$(CC) $(COPS) -o execls execls.c

execcmd: execcmd.c
	$(CC) $(COPS) -o execcmd execcmd.c restart.c

execcmdargv: execcmdargv.c makeargv.c
	$(CC) $(COPS) -o execcmdargv execcmdargv.c makeargv.c restart.c

runback: runback.c makeargv.c
	$(CC) $(COPS) -o runback runback.c makeargv.c

showreturnstatustest: showreturnstatustest.c showreturnstatus.c
	$(CC) $(COPS) -o showreturnstatustest showreturnstatustest.c showreturnstatus.c restart.c

lintall: lintoutputPID lintoutputIDs lintsimplefork linttwoprocs lintbadprocessID lintsimplechain lintsimplefan lintfanwait lintfanwaitmsg lintchainwaitmsg lintparentwaitpid lintexecls lintexeccmd lintexeccmdargv lintrunback lintshowreturnstatus

lintoutputPID:
	$(LINT) $(LOPS) outputPID.c

lintoutputIDs:
	$(LINT) $(LOPS) outputIDs.c

lintsimplefork:
	$(LINT) $(LOPS) simplefork.c

linttwoprocs:
	$(LINT) $(LOPS) twoprocs.c

lintbadprocessID:
	$(LINT) $(LOPS) badprocessID.c

lintsimplechain:
	$(LINT) $(LOPS) simplechain.c

lintsimplefan:
	$(LINT) $(LOPS) simplefan.c

lintfanwait:
	$(LINT) $(LOPS) fanwait.c r_wait.c

lintfanwaitmsg:
	$(LINT) $(LOPS) fanwaitmsg.c

lintchainwaitmsg:
	$(LINT) $(LOPS) chainwaitmsg.c

lintparentwaitpid:
	$(LINT) $(LOPS) parentwaitpid.c

lintexecls:
	$(LINT) $(LOPS) execls.c

lintexeccmd:
	$(LINT) $(LOPS) execcmd.c restart.c

lintexeccmdargv:
	$(LINT) $(LOPS) execcmdargv.c makeargv.c restart.c

lintrunback:
	$(LINT) $(LOPS) runback.c makeargv.c

lintshowreturnstatus:
	$(LINT) $(LOPS) showreturnstatustest.c showreturnstatus.c restart.c

clean:
	rm -f *.o core outputPID outputIDs simplefork twoprocs badprocessID simplechain simplefan parentwaitpid fanwait fanwaitmsg fanwaitpid chainwaitmsg execls execcmd execcmdargv runback showreturnstatustest


