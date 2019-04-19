CC = cc
COPS =
LINT = lint
LOPS = -x -u

all: makefileinfo

makefileinfo: makefileinfo.c restart.c
	$(CC) $(COPS) -o makefileinfo makefileinfo.c restart.c

lintall: lint

lint:
	$(LINT)lint $(LOPS) makefileinfo.c restart.c

clean:
	rm -f *.o makefileinfo
