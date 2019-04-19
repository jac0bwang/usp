CC = cc
COPS =
LINT = lint
LOPS = -x -u
LIBTHREAD = -lpthread
RTLIB = -lrt

all: chaincritical semsharedtest maincritical maincriticalsem named

named: chainnamed destroynamedtest

chaincritical: chaincritical.c restart.c
	$(CC) $(COPS) -o chaincritical chaincritical.c restart.c

semsharedtest: semsharedtest.c semshared.c
	$(CC) $(COPS) -o semsharedtest semsharedtest.c semshared.c $(LIBTHREAD) $(RTLIB)

maincritical: maincritical.c threadcritical.c
	$(CC) $(COPS) -o maincritical maincritical.c threadcritical.c $(RTLIB) $(LIBTHREAD)

maincriticalsem: maincriticalsem.c threadcriticalsem.c
	$(CC) $(COPS) -o maincriticalsem maincriticalsem.c threadcriticalsem.c $(RTLIB) $(LIBTHREAD)

chainnamed: chainnamed.c getnamed.c restart.c
	$(CC) $(COPS) -o chainnamed chainnamed.c getnamed.c restart.c $(RTLIB)

destroynamedtest: destroynamedtest.c destroynamed.c getnamed.c
	$(CC) $(COPS) -o destroynamedtest destroynamedtest.c destroynamed.c getnamed.c $(RTLIB)

lintall: lintchaincritical lintsemshared lintmaincritical lintmaincriticalsem lintchainnamed lintdestroynamed

lintchaincritical:
	$(LINT) $(LOPS) chaincritical.c

lintsemshared:
	$(LINT) $(LOPS) semsharedtest.c semshared.c

lintmaincritical:
	$(LINT) $(LOPS) maincritical.c threadcritical.c

lintmaincriticalsem:
	$(LINT) $(LOPS) maincritical.c threadcriticalsem.c

lintchainnamed:
	$(LINT) $(LOPS) chainnamed.c getnamed.c

lintdestroynamed:
	$(LINT) $(LOPS) destroynamedtest.c destroynamed.c getnamed.c

clean:
	rm -f *.o core chaincritical semsharedtest maincritical maincriticalsem chainnamed destroynamedtest
