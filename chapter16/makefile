CC = cc
COPS =
LINT = lint
LOPS = -x -u
LIBTHREAD = -lpthread
POSIXTHREAD = -D_POSIX_PTHREAD_SEMANTICS
RTLIB = -lrt

all:  randpcforeversem randpcforevercond randpcdone randpcsig isregulartest

randpcforeversem: randpcforever.c randconsumer.c randproducer.c buffersem.c globalerror.c randsafe.c sharedsum.c showresults.c
	$(CC) $(COPS) -o randpcforeversem randpcforever.c randconsumer.c randproducer.c buffersem.c globalerror.c randsafe.c sharedsum.c showresults.c -lm $(RTLIB) $(LIBTHREAD)

randpcforevercond: randpcforever.c randconsumer.c randproducer.c buffercond.c globalerror.c randsafe.c sharedsum.c showresults.c
	$(CC) $(COPS) -o randpcforevercond randpcforever.c randconsumer.c randproducer.c buffercond.c globalerror.c randsafe.c sharedsum.c showresults.c -lm $(RTLIB) $(LIBTHREAD)

randpcdone: randpcdone.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c showresults.c
	$(CC) $(COPS) -o randpcdone randpcdone.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c showresults.c -lm $(RTLIB) $(LIBTHREAD)

randpcsig: randpcsig.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c signalthread.c showresults.c 
	$(CC) $(COPS) -o randpcsig randpcsig.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c signalthread.c showresults.c -lm $(RTLIB) $(LIBTHREAD) $(POSIXTHREAD)

isregulartest: isregulartest.c isregular.c
	$(CC) $(COPS) -o isregulartest isregulartest.c isregular.c

lintall: lintbufferbad lintbuffer lintbufferseminit lintbufferinitmutex lintbufferinitonce lintrandpcforeversem lintrandpcforevercond lintrandpcdone lintrandpcsig lintisregular

lintbufferbad:
	$(LINT) $(LOPS) bufferbad.c

lintbuffer:
	$(LINT) $(LOPS) buffer.c

lintbufferseminit:
	$(LINT) $(LOPS) bufferseminit.c

lintbufferinitmutex:
	$(LINT) $(LOPS) bufferinitmutex.c

lintbufferinitonce:
	$(LINT) $(LOPS) bufferinitonce.c

lintrandpcforeversem:
	$(LINT) $(LOPS) randpcforever.c randconsumer.c randproducer.c buffersem.c globalerror.c randsafe.c sharedsum.c showresults.c -lm

lintrandpcforevercond:
	$(LINT) $(LOPS) randpcforever.c randconsumer.c randproducer.c buffercond.c globalerror.c randsafe.c sharedsum.c showresults.c -lm

lintrandpcdone:
	$(LINT) $(LOPS) randpcdone.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c showresults.c -lm

lintrandpcsig:
	$(LINT) $(LOPS) $(POSIXTHREAD) randpcsig.c randconsumerdone.c randproducerdone.c bufferconddone.c globalerror.c randsafe.c sharedsum.c signalthread.c showresults.c -lm

lintisregular:
	$(LINT) $(LOPS) isregulartest.c isregular.c 

clean:
	rm -f *.o core randpcforeversem randpcforevercond randpcdone randpcsig isregulartest
