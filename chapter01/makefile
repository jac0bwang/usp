CC = cc
COPS = 
LINT = lint
LOPS = -x -u

all: checkpasstest

checkpasstest: checkpasstest.c checkpass.c
	$(CC) $(COPS) -o checkpasstest checkpasstest.c checkpass.c

lintall: lint

lint:
	$(LINT) $(LOPS) checkpasstest.c checkpass.c

clean:
	rm -f *.o core checkpasstest


