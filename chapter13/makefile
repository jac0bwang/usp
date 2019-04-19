CC = cc
COPS =
LINT = lint
LOPS = -x -u
LIBTHREAD = -lpthread
POSIXPTHREAD = -D_POSIX_PTHREAD_SEMANTICS
RTLIB = -lrt

all: countertest computethreadmain computethreadsig testandsetoncetest printinitmutextest printinitoncetest tbarriertest strerrortest

computethreadmain: computethreadmain.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c
	$(CC) $(COPS) -o computethreadmain computethreadmain.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c -lm $(RTLIB) $(LIBTHREAD)

computethreadsig: computethreadsig.c signalthread.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c
	$(CC) $(COPS) -o computethreadsig computethreadsig.c signalthread.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c -lm $(RTLIB) $(LIBTHREAD) $(POSIXPTHREAD)

printandinitializeoncetest: printandinitializeoncetest.c printandinitializeonce.c
	$(CC) $(COPS) -o printandinitializeoncetest printandinitializeoncetest.c printandinitializeonce.c $(LIBTHREAD)

countertest: countertest.c counter.c wastetime.c
	$(CC) $(COPS) -o countertest countertest.c counter.c wastetime.c $(LIBTHREAD)

testandsetoncetest: testandsetoncetest.c testandsetonce.c
	$(CC) $(COPS) -o testandsetoncetest testandsetoncetest.c testandsetonce.c $(LIBTHREAD)

printinitmutextest: printinitmutextest.c printinitmutex.c
	$(CC) $(COPS) -o printinitmutextest printinitmutextest.c printinitmutex.c $(LIBTHREAD)

printinitoncetest: printinitoncetest.c printinitonce.c
	$(CC) $(COPS) -o printinitoncetest printinitoncetest.c printinitonce.c $(LIBTHREAD)

tbarriertest: tbarriertest.c tbarrier.c
	$(CC) $(COPS) -o tbarriertest tbarriertest.c tbarrier.c $(LIBTHREAD)

strerrortest: strerrortest.c strerror_r.c
	$(CC) $(COPS) -o strerrortest strerrortest.c strerror_r.c $(LIBTHREAD)

lintall: lintcomputethread lintcomputethreadsig linttestandsetonce lintprintinitmutex lintprintinitonce linttbarriertest lintstrerrortest lintcountertest lintlistlibr lintbarrier lintlistlibrw

lintcomputethread:
	$(LINT) $(LOPS) computethreadmain.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c -lm

lintcomputethreadsig:
	$(LINT) $(LOPS) $(POSIXPTHREAD) computethreadsig.c signalthread.c computethread.c sharedsum.c globalerror.c doneflag.c randsafe.c showresults.c -lm $(POISXPTHREAD)


linttestandsetonce:
	$(LINT) $(LOPS) testandsetoncetest.c testandsetonce.c

lintprintinitmutex:
	$(LINT) $(LOPS) printinitmutextest.c printinitmutex.c

lintprintinitonce:
	$(LINT) $(LOPS) printinitoncetest.c printinitonce.c

linttbarriertest:
	$(LINT) $(LOPS) tbarriertest.c tbarrier.c

lintstrerrortest:
	$(LINT) $(LOPS) strerrortest.c strerror_r.c

lintcountertest:
	$(LINT) $(LOPS) countertest.c counter.c wastetime.c

lintlistlibr:
	$(LINT) $(LOPS) listlibn.c

lintbarrier:
	$(LINT) $(LOPS) tbarrier.c

lintlistlibrw:
	$(LINT) $(LOPS) listlibrw.c

clean:
	rm -f *.o core computethreadmain computethreadsig countertest testandsetoncetest printinitmutextest tabrriertest printinitoncetest tbarriertest strerrortest
