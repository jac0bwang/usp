CC = cc
COPS = 
LINT = lint
LOPS = -x -u

all: getcwdpathmax getcwdpathconf shownames printaccesstest printaccessmodbadtest printaccessmodtest isdirectorytest simplebiff

getcwdpathmax: getcwdpathmax.c
	$(CC) $(COPS) -o getcwdpathmax getcwdpathmax.c

getcwdpathconf: getcwdpathconf.c
	$(CC) $(COPS) -o getcwdpathconf getcwdpathconf.c

shownames: shownames.c
	$(CC) $(COPS) -o shownames shownames.c

printaccesstest: printaccesstest.c printaccess.c
	$(CC) $(COPS) -o printaccesstest printaccesstest.c  printaccess.c

printaccessmodbadtest: printaccessmodbadtest.c printaccessmodbad.c
	$(CC) $(COPS) -o printaccessmodbadtest printaccessmodbadtest.c  printaccessmodbad.c

printaccessmodtest: printaccessmodtest.c printaccessmod.c
	$(CC) $(COPS) -o printaccessmodtest printaccessmodtest.c  printaccessmod.c

isdirectorytest: isdirectorytest.c isdirectory.c
	$(CC) $(COPS) -o isdirectorytest isdirectorytest.c  isdirectory.c

simplebiff: simplebiff.c
	$(CC) $(COPS) -o simplebiff simplebiff.c

lintall: lintgetcwdpathmax lintgetcwdpathconf lintshownames lintprintaccess lintprintaccessmodbad lintprintaccessmod lintisdirectory lintsimplebiff

lintgetcwdpathmax:
	$(LINT) $(LOPS) getcwdpathmax.c

lintgetcwdpathconf:
	$(LINT) $(LOPS) getcwdpathconf.c

lintshownames:
	$(LINT) $(LOPS) shownames.c

lintprintaccess:
	$(LINT) $(LOPS) printaccesstest.c printaccess.c

lintprintaccessmodbad:
	$(LINT) $(LOPS) printaccessmodbadtest.c printaccessmodbad.c

lintprintaccessmod:
	$(LINT) $(LOPS) printaccessmodtest.c printaccessmod.c

lintisdirectory:
	$(LINT) $(LOPS) isdirectorytest.c isdirectory.c

lintsimplebiff:
	$(LINT) $(LOPS) simplebiff.c

clean:
	rm -f *.o core getcwdpathmax getcwdpathconf shownames printaccesstest printaccessmodbadtest printaccessmodtest isdirectorytest simplebiff
