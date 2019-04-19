CC = cc
COPS =
LINT = lint
LOPS = -x -u
REENT = -D_REENTRANT

all: largearrayinit largearray argtest argtestfree getpathstest wordaveragetestbad wordaveragetest bubblesorttest keeplog showtimes environ getpathstest showtimestest

largearrayinit: largearrayinit.c
	$(CC) $(COPS) -o largearrayinit largearrayinit.c

largearray: largearray.c
	$(CC) $(COPS) -o largearray largearray.c

argtest: argtest.c makeargv.c
	$(CC) $(COPS) -o argtest argtest.c makeargv.c

argtestfree: argtestfree.c makeargv.c freemakeargv.c
	$(CC) $(COPS) -o argtestfree argtestfree.c makeargv.c freemakeargv.c

wordaveragetestbad: wordaveragetest.c wordaveragebad.c
	$(CC) $(COPS) -o wordaveragetestbad wordaveragetest.c wordaveragebad.c

wordaveragetest: wordaveragetest.c wordaverage.c
	$(CC) $(COPS) $(REENT) -o wordaveragetest wordaveragetest.c wordaverage.c

bubblesorttest: bubblesorttest.c bubblesort.c
	$(CC) $(COPS) -o bubblesorttest bubblesorttest.c bubblesort.c

keeplog: keeplog.c keeploglib.c listlib.c listlib.h
	$(CC) $(COPS) -o keeplog keeplog.c keeploglib.c listlib.c

showtimes: showtimes.c
	$(CC) $(COPS) -o showtimes showtimes.c

environ: environ.c
	$(CC) $(COPS) -o environ environ.c

getpathstest: getpathstest.c makeargv.c getpaths.c
	$(CC) $(COPS) -o getpathstest getpathstest.c makeargv.c getpaths.c

showtimestest: showtimestest.c wastetime.c
	$(CC) $(COPS) -o showtimestest showtimestest.c wastetime.c


lintall: lintlargearray lintlargearrayinit lintargtest lintargtestfree lintwordaveragebad lintwordaverage lintbubble lintkeeplog lintshowtimes lintenviron lintgetpathstest lintloglib lintshowtimestest

lintlargearrayinit:
	$(LINT) $(LOPS) largearrayinit.c

lintlargearray:
	$(LINT) $(LOPS) largearray.c

lintargtest:
	$(LINT) $(LOPS) argtest.c makeargv.c

lintargtestfree:
	$(LINT) $(LOPS) argtestfree.c makeargv.c freemakeargv.c

lintwordaveragebad:
	$(LINT) $(LOPS) wordaveragetest.c wordaveragebad.c

lintwordaverage:
	$(LINT) $(LOPS) $(REENT) wordaveragetest.c wordaverage.c

lintbubble:
	$(LINT) $(LOPS) bubblesorttest.c bubblesort.c

lintkeeplog:
	$(LINT) $(LOPS) keeplog.c keeploglib.c listlib.c

lintshowtimes:
	$(LINT) $(LOPS) showtimes.c

lintenviron:
	$(LINT) $(LOPS) environ.c

lintgetpathstest:
	$(LINT) $(LOPS) getpathstest.c makeargv.c getpaths.c

lintloglib:
	$(LINT) $(LOPS) loglib.c

lintshowtimestest:
	$(LINT) $(LOPS) showtimestest.c wastetime.c

clean:
	rm -f *.o core wordaveragetest wordaveragetestbad bubblesorttest keeplog largearray largearrayinit showtimes environ argtest argtestfree getpathstest showtimestest


