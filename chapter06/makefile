CC = cc
COPS =
LINT = lint
LOPS = -x -u

all: parentwritepipe parentwritepipe1 parentwritepipe2 synchronizefan simpleredirect parentchildfifo pipeserver pipeclient seqserverbad seqclientbad passwordnosigstest setnoncanonicaltest
audio: audiocopy nonblockingaudio

parentwritepipe: parentwritepipe.c
	$(CC) $(COPS) -o parentwritepipe parentwritepipe.c

parentwritepipe1: parentwritepipe1.c restart.c restart.h
	$(CC) $(COPS) -o parentwritepipe1 parentwritepipe1.c restart.c

parentwritepipe2: parentwritepipe2.c restart.c restart.h
	$(CC) $(COPS) -o parentwritepipe2 parentwritepipe2.c restart.c

synchronizefan: synchronizefan.c restart.c restart.h
	$(CC) $(COPS) -o synchronizefan synchronizefan.c restart.c

simpleredirect: simpleredirect.c
	$(CC) $(COPS) -o simpleredirect simpleredirect.c

parentchildfifo: parentchildfifo.c dofifochild.c dofifoparent.c restart.c
	$(CC) $(COPS) -o parentchildfifo parentchildfifo.c dofifochild.c dofifoparent.c restart.c

pipeserver: pipeserver.c restart.c restart.h
	$(CC) $(COPS) -o pipeserver pipeserver.c restart.c

pipeclient: pipeclient.c restart.c restart.h
	$(CC) $(COPS) -o pipeclient pipeclient.c restart.c

seqserverbad: seqserverbad.c restart.c restart.h
	$(CC) $(COPS) -o seqserverbad seqserverbad.c restart.c

seqclientbad: seqclientbad.c restart.c restart.h
	$(CC) $(COPS) -o seqclientbad seqclientbad.c restart.c

passwordnosigstest: passwordnosigstest.c passwordnosigs.c setecho.c restart.c restart.h
	$(CC) $(COPS) -o passwordnosigstest passwordnosigstest.c passwordnosigs.c setecho.c restart.c

setnoncanonicaltest: setnoncanonicaltest.c setnoncanonical.c savetermios.c ttysetchar.c restart.c
	$(CC) $(COPS) -o setnoncanonicaltest setnoncanonicaltest.c setnoncanonical.c savetermios.c ttysetchar.c restart.c

audiocopy: audiocopy.c audiolib.c audiolib.h restart.c
	$(CC) $(COPS) -o audiocopy audiocopy.c audiolib.c restart.c

nonblockingaudio: nonblockingaudio.c restart.c
	$(CC) $(COPS) -o nonblockingaudio nonblockingaudio.c restart.c

lintall: lintparentwritepipe lintparentwritepipe1 lintparentwritepipe2 lintsynchronizefan lintsimpleredirect lintparentchildfifo lintpipeserver lintpipeclient lintseqserverbad lintseqclientbad lintpasswordnosigs lintsetnoncanonical

lintaudio: lintaudiocopy lintnonblockingaudio

lintparentwritepipe:
	$(LINT) $(LOPS) parentwritepipe.c

lintparentwritepipe1:
	$(LINT) $(LOPS) parentwritepipe1.c restart.c

lintparentwritepipe2:
	$(LINT) $(LOPS) parentwritepipe2.c restart.c

lintsynchronizefan:
	$(LINT) $(LOPS) synchronizefan.c restart.c

lintsimpleredirect:
	$(LINT) $(LOPS) simpleredirect.c

lintparentchildfifo:
	$(LINT) $(LOPS) parentchildfifo.c dofifochild.c dofifoparent.c restart.c

lintpipeserver:
	$(LINT) $(LOPS) pipeserver.c restart.c

lintpipeclient:
	$(LINT) $(LOPS) pipeclient.c restart.c

lintseqserverbad:
	$(LINT) $(LOPS) seqserverbad.c restart.c

lintseqclientbad:
	$(LINT) $(LOPS) seqclientbad.c restart.c

lintpasswordnosigs:
	$(LINT) $(LOPS) passwordnosigstest.c passwordnosigs.c setecho.c restart.c

lintsetnoncanonical:
	$(LINT) $(LOPS) setnoncanonicaltest.c setnoncanonical.c savetermios.c ttysetchar.c restart.c

lintaudiocopy:
	$(LINT) $(LOPS) audiocopy.c audiolib.c restart.c

lintnonblockingaudio:
	$(LINT) $(LOPS) nonblockingaudio.c restart.c

clean:
	rm -f *.o core parentwritepipe parentwritepipe1 parentwritepipe2 parentchildfifo temppipe synchronizefan simpleredirect parentwritepipe pipeserver pipeclient seqserverbad seqclientbad passwordnosigstest setnoncanonicaltest audiocopy nonblockingaudio
