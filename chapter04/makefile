CC = cc
COPS =
LINT = lint
LOPS = -x -u

all: readlinetest simplecopy1 simplecopy copyfilemain whichisreadytest readtimedtest monitorfork copy2filestest monitorselecttest monitorpolltest bufferout bufferinout openfork forkopen fileiofork fileioforkline redirect chainopenfork chainforkopen chainforkopenseek chainforkopenlog setblocktest process_or_do_work_test

fileio_fork: fileio_fork.c
	$(CC) $(COPS) -o fileio_fork fileio_fork.c

fileio_fork_line: fileio_fork_line.c
	$(CC) $(COPS) -o fileio_fork_line fileio_fork_line.c

readlinetest: readlinetest.c readline.c
	$(CC) $(COPS) -o readlinetest readlinetest.c readline.c

simplecopy1: simplecopy.c copyfile1.c
	$(CC) $(COPS) -o simplecopy1 simplecopy.c copyfile1.c

simplecopy: simplecopy.c r_read.c r_write.c copyfile.c restart.h
	$(CC) $(COPS) -o simplecopy simplecopy.c r_read.c r_write.c copyfile.c

copyfilemain: copyfilemain.c r_read.c r_write.c copyfile.c restart.h
	$(CC) $(COPS) -o copyfilemain copyfilemain.c r_read.c r_write.c copyfile.c

whichisreadytest: whichisreadytest.c whichisready.c
	$(CC) $(COPS) -o whichisreadytest whichisreadytest.c whichisready.c

readtimedtest: readtimedtest.c readtimed.c waitfdtimed.c restart.h
	$(CC) $(COPS) -o readtimedtest readtimedtest.c readtimed.c waitfdtimed.c r_read.c r_write.c

monitorfork: monitorfork.c restart.c
	$(CC) $(COPS) -o monitorfork monitorfork.c restart.c

copy2filestest: copy2filestest.c copy2files.c readwrite.c r_read.c r_write.c
	$(CC) $(COPS) -o copy2filestest copy2filestest.c copy2files.c readwrite.c r_read.c r_write.c

monitorselecttest: monitorselecttest.c monitorselect.c
	$(CC) $(COPS) -o monitorselecttest monitorselecttest.c monitorselect.c restart.c

monitorpolltest: monitorpolltest.c monitorpoll.c
	$(CC) $(COPS) -o monitorpolltest monitorpolltest.c monitorpoll.c restart.c

bufferout: bufferout.c
	$(CC) $(COPS) -o bufferout bufferout.c

bufferinout: bufferinout.c
	$(CC) $(COPS) -o bufferinout bufferinout.c

openfork: openfork.c
	$(CC) $(COPS) -o openfork openfork.c

forkopen: forkopen.c
	$(CC) $(COPS) -o forkopen forkopen.c

fileiofork: fileiofork.c
	$(CC) $(COPS) -o fileiofork fileiofork.c

fileioforkline: fileioforkline.c
	$(CC) $(COPS) -o fileioforkline fileioforkline.c

chainopenfork: chainopenfork.c
	$(CC) $(COPS) -o chainopenfork chainopenfork.c

chainforkopen: chainforkopen.c
	$(CC) $(COPS) -o chainforkopen chainforkopen.c

chainforkopenseek: chainforkopenseek.c
	$(CC) $(COPS) -o chainforkopenseek chainforkopenseek.c

chainforkopenlog: chainforkopenlog.c atomic_logger.c atomic_logger.h
	$(CC) $(COPS) -o chainforkopenlog chainforkopenlog.c atomic_logger.c

redirect: redirect.c
	$(CC) $(COPS) -o redirect redirect.c restart.c

setblocktest: setblocktest.c setblock.c setnonblock.c
	$(CC) $(COPS) -o setblocktest setblocktest.c setblock.c setnonblock.c

process_or_do_work_test: process_or_do_work_test.c process_or_do_work_test.c setnonblock.c
	$(CC) $(COPS) -o process_or_do_work_test process_or_do_work_test.c process_or_do_work.c setnonblock.c restart.c

lintall: lintreadlinetest lintsimplecopy1 lintsimplecopy lintreadblock lintreadwriteblock lintcopyfilemain lintrclose lintwhichisready lintreadtimedtest lintmonitorfork lintcopy2filestest lintmonitorselecttest lintforkopen lintfileiofork lintredirect lintchainopenfork lintchainforkopen lintchainforkopenseek lintchainforkopenlog lintsetblocktest lintprocessordowork

lintreadlinetest:
	$(LINT) $(LOPS) readlinetest.c readline.c

lintsimplecopy1:
	$(LINT) $(LOPS) simplecopy.c copyfile1.c

lintsimplecopy:
	$(LINT) $(LOPS) simplecopy.c r_read.c r_write.c copyfile.c

lintreadblock:
	$(LINT) $(LOPS) readblock.c

lintreadwriteblock:
	$(LINT) $(LOPS) readwriteblock.c

lintcopyfilemain:
	$(LINT) $(LOPS) copyfilemain.c r_read.c r_write.c copyfile.c

lintrclose:
	$(LINT) $(LOPS) r_close.c

lintwhichisready:
	$(LINT) $(LOPS) whichisreadytest.c whichisready.c

lintreadtimedtest:
	$(LINT) $(LOPS) readtimedtest.c readtimed.c waitfdtimed.c

lintmonitorfork:
	$(LINT) $(LOPS) monitorfork.c restart.c 

lintcopy2filestest:
	$(LINT) $(LOPS) copy2filestest.c copy2files.c readwrite.c r_read.c r_write.c

lintmonitorselecttest:
	$(LINT) $(LOPS) monitorselecttest.c monitorselect.c restart.c

lintmonitorpolltest:
	$(LINT) $(LOPS) $(LINUXOPS) monitorpolltest.c monitorpoll.c restart.c

lintbufferout:
	$(LINT) $(LOPS) bufferout.c

lintbufferinout:
	$(LINT) $(LOPS) bufferinout.c

lintopenfork:
	$(LINT) $(LOPS) openfork.c

lintforkopen:
	$(LINT) $(LOPS) forkopen.c

lintfileiofork:
	$(LINT) $(LOPS) fileiofork.c

lintfileioforkline:
	$(LINT) $(LOPS) fileioforkline.c

lintredirect:
	$(LINT) $(LOPS) redirect.c restart.c

lintchainopenfork:
	$(LINT) $(LOPS) chainopenfork.c

lintchainforkopen:
	$(LINT) $(LOPS) chainforkopen.c

lintchainforkopenseek:
	$(LINT) $(LOPS) chainforkopenseek.c

lintchainforkopenlog:
	$(LINT) $(LOPS) chainforkopenlog.c

lintsetblocktest:
	$(LINT) $(LOPS) setblocktest.c setblock.c setnonblock.c

lintprocessordowork:
	$(LINT) $(LOPS) process_or_do_work_test.c process_or_do_work.c setnonblock.c restart.c

clean:
	rm -f *.o readlinetest simplecopy1 simplecopy copyfilemain whichisreadytest readtimedtest monitorfork copy2filestest monitorselecttest monitorpolltest bufferout bufferinout openfork forkopen fileiofork fileioforkline redirect chainopenfork chainforkopen chainforkopenseek chainforkopenlog setblocktest process_or_do_work_test mypipe pipe1 pipe2 outfile
