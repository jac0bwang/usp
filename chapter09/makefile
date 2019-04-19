CC = cc
COPS =
LINT = lint
LOPS = -x -u
RTLIB = -lrt

all: simpletiming timeprint badtiming gettimeofdaytiming gettimeofdaytest realtime cpufraction timechild beeper nanotest periodicasterisk xsitimer load_cpu multikill

realtime: clockrealtimetiming clockrealtimetest abstime sendsigqueue sigqueuehandler tmrtimer timesignals periodicmessage

simpletiming: simpletiming.c functiontotime.c
	$(CC) $(COPS) -o simpletiming simpletiming.c functiontotime.c

timeprint: timeprint.c
	$(CC) $(COPS) -o timeprint timeprint.c

badtiming: badtiming.c functiontotime.c
	$(CC) $(COPS) -o badtiming badtiming.c functiontotime.c

gettimeofdaytiming: gettimeofdaytiming.c functiontotime.c
	$(CC) $(COPS) -o gettimeofdaytiming gettimeofdaytiming.c functiontotime.c

gettimeofdaytest: gettimeofdaytest.c
	$(CC) $(COPS) -o gettimeofdaytest gettimeofdaytest.c

clockrealtimetiming: clockrealtimetiming.c
	$(CC) $(COPS) -o clockrealtimetiming clockrealtimetiming.c functiontotime.c $(RTLIB)

clockrealtimetest: clockrealtimetest.c
	$(CC) $(COPS) -o clockrealtimetest clockrealtimetest.c $(RTLIB)

cpufraction: cpufraction.c functiontotime.c
	$(CC) $(COPS) -o cpufraction cpufraction.c functiontotime.c

timechild: timechild.c restart.c
	$(CC) $(COPS) -o timechild timechild.c restart.c

beeper: beeper.c
	$(CC) $(COPS) -o beeper beeper.c

nanotest: nanotest.c
	$(CC) $(COPS) -o nanotest nanotest.c $(RTLIB)

periodicasterisk: periodicasterisk.c
	$(CC) $(COPS) -o periodicasterisk periodicasterisk.c

xsitimer: xsitimer.c functiontotime.c
	$(CC) $(COPS) -o xsitimer xsitimer.c functiontotime.c

periodicmessage: periodicmessage.c
	$(CC) $(COPS) -o periodicmessage periodicmessage.c $(RTLIB)

tmrtimer: tmrtimer.c functiontotime.c
	$(CC) $(COPS) -o tmrtimer tmrtimer.c functiontotime.c $(RTLIB)

sendsigqueue: sendsigqueue.c
	$(CC) $(COPS) -o sendsigqueue sendsigqueue.c $(RTLIB)

sigqueuehandler: sigqueuehandler.c
	$(CC) $(COPS) -o sigqueuehandler sigqueuehandler.c

abstime: abstime.c abstimelib.c
	$(CC) $(COPS) -o abstime abstime.c abstimelib.c $(RTLIB)

load_cpu: load_cpu.c
	$(CC) $(COPS) -o load_cpu load_cpu.c

timesignals: timesignals.c
	$(CC) $(COPS) -o timesignals timesignals.c

multikill: multikill.c
	$(CC) $(COPS) -o multikill multikill.c

lintall: lintsimpletiming linttimeprint lintbadtiming lintgettimeofdaytiming lintgettimeofdaytest lintcpufraction lintclockrealtimetiming lintclockrealtimetest linttimechild lintbeeper lintnanotest lintperiodicasterisk lintxsitimer lintperiodicmessage linttmrtimer lintsendsigqueue lintsigqueuehandler lintabstime lintloadcpu linttimesignals lintmultikill

lintsimpletiming:
	$(LINT) $(LOPS) simpletiming.c functiontotime.c

linttimeprint:
	$(LINT) $(LOPS) timeprint.c

lintbadtiming:
	$(LINT) $(LOPS) badtiming.c functiontotime.c

lintgettimeofdaytiming:
	$(LINT) $(LOPS) gettimeofdaytiming.c functiontotime.c

lintgettimeofdaytest:
	$(LINT) $(LOPS) gettimeofdaytest.c

lintcpufraction:
	$(LINT) $(LOPS) cpufraction.c functiontotime.c

lintclockrealtimetiming:
	$(LINT) $(LOPS) clockrealtimetiming.c functiontotime.c

lintclockrealtimetest:
	$(LINT) $(LOPS) clockrealtimetest.c

linttimechild:
	$(LINT) $(LOPS) timechild.c

lintbeeper:
	$(LINT) $(LOPS) beeper.c

lintnanotest:
	$(LINT) $(LOPS) nanotest.c

lintperiodicasterisk:
	$(LINT) $(LOPS) periodicasterisk.c

lintxsitimer:
	$(LINT) $(LOPS) xsitimer.c functiontotime.c

lintperiodicmessage:
	$(LINT) $(LOPS) periodicmessage.c

linttmrtimer:
	$(LINT) $(LOPS) tmrtimer.c functiontotime.c

lintsendsigqueue:
	$(LINT) $(LOPS) sendsigqueue.c

lintsigqueuehandler:
	$(LINT) $(LOPS) sigqueuehandler.c

lintabstime:
	$(LINT) $(LOPS) abstime.c abstimelib.c

lintloadcpu:
	$(LINT) $(LOPS) load_cpu.c

linttimesignals:
	$(LINT) $(LOPS) timesignals.c

lintmultikill:
	$(LINT) $(LOPS) multikill.c

clean:
	rm -f core *.o simpletiming timeprint badtiming clockrealtimetiming clockrealtimetest gettimeofdaytiming gettimeofdaytest cpufraction timechild beeper nanotest periodicasterisk xsitimer periodicmessage tmrtimer sendsigqueue sigqueuehandler abstime load_cpu timesignals multikill


