CC = cc
COPS =
LINT = lint
LOPS = -x -u

all: ush1 ush2 ush2r ush2p ush3 ush4 ush5 ush6 ush7 showid showidsleep showidsleepignore

ush1: ush1.c makeargv.c
	$(CC) $(COPS) -o ush1 ush1.c makeargv.c

ush2: ush2.c executecmdsimple.c makeargv.c
	$(CC) $(COPS) -o ush2 ush2.c executecmdsimple.c makeargv.c

ush2r: ush2.c executecmdredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush2r ush2.c executecmdredirect.c makeargv.c parseandredirect.c 

ush2p: ush2.c executecmdpipe.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush2p ush2.c executecmdpipe.c executeredirect.c makeargv.c parseandredirect.c

ush3:   ush3.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush3 ush3.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

ush4:   ush4.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush4 ush4.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

ush5:   ush5.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush5 ush5.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

ush6:   ush6.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush6 ush6.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

ush7:   ush7.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c
	$(CC) $(COPS) -o ush7 ush7.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

showid: showid.c
	$(CC) $(COPS) -o showid showid.c

showidsleep: showidsleep.c
	$(CC) $(COPS) -o showidsleep showidsleep.c

showidsleepignore: showidsleepignore.c
	$(CC) $(COPS) -o showidsleepignore showidsleepignore.c

lintall: lint1 lint2 lint2r lint2p lint3 lint4 lint5 lint6 lint7 lintshow lintshowsleep lintshowsleepignore

lint1:
	$(LINT) $(LOPS) ush1.c makeargv.c

lint2:
	$(LINT) $(LOPS) ush2.c executecmdsimple.c makeargv.c

lint2r:
	$(LINT) $(LOPS) ush2.c executecmdredirect.c makeargv.c parseandredirect.c

lint2p:
	$(LINT) $(LOPS) ush2.c executecmdpipe.c executeredirect.c makeargv.c parseandredirect.c

lint3:
	$(LINT) $(LOPS) ush3.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

lint4:
	$(LINT) $(LOPS) ush4.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

lint5:
	$(LINT) $(LOPS) ush5.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

lint6:
	$(LINT) $(LOPS) ush6.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

lint7:
	$(LINT) $(LOPS) ush7.c executecmdpipe.c signalsetup.c executeredirect.c makeargv.c parseandredirect.c

lintshow:
	$(LINT) showid.c

lintshowsleep:
	$(LINT) showidsleep.c

lintshowsleepignore:
	$(LINT) showidsleepignore.c

clean:
	rm -f *.o core ush1 ush2 ush2r ush2p ush3 ush4 ush5 ush6 ush7 showid showidsleep showidsleepignore
