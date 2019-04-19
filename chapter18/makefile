CC = cc
COPS =
LINT = lint
LOPS = -x -u
NETLIBS = -lsocket -lnsl

all: client server serverp serverp2 client2 server2 reflectserver reflectclient

audio: client_audio

server: server.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o server server.c restart.c uici.c uiciname.c $(NETLIBS)

serverp: serverp.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o serverp serverp.c restart.c uici.c uiciname.c $(NETLIBS)

serverp2: serverp2.c copy2files.c restart.c uici.c uiciname.c 
	$(CC) $(COPS) -o serverp2 serverp2.c copy2files.c restart.c uici.c uiciname.c $(NETLIBS)

reflectserver: reflectserver.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o reflectserver reflectserver.c restart.c uici.c uiciname.c $(NETLIBS)

client: client.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o client client.c restart.c uici.c uiciname.c $(NETLIBS)

reflectclient: reflectclient.c restart.c uici.c uiciname.c 
	$(CC) $(COPS) -o reflectclient reflectclient.c restart.c uici.c uiciname.c $(NETLIBS)

client2: client2.c copy2files.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o client2 client2.c copy2files.c restart.c uici.c uiciname.c $(NETLIBS)

server2: server2.c copy2files.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o server2 server2.c copy2files.c restart.c uici.c uiciname.c $(NETLIBS)

client_audio: client_audio.c hasvoice.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o client_audio client_audio.c hasvoice.c restart.c uici.c uiciname.c $(NETLIBS) -L/usr/demo/SOUND/lib -laudio

lintall: lints lintsp lintsp2 lintsr lintc lintcr lintca lintc2 lints2

lints:
	$(LINT) $(LOPS) server.c restart.c uici.c uiciname.c

lintsp:
	$(LINT) $(LOPS) serverp.c restart.c uici.c uiciname.c copy2files.c

lintsp2:
	$(LINT) $(LOPS) serverp2.c restart.c uici.c uiciname.c

lintsr:
	$(LINT) $(LOPS) reflectserver.c restart.c uici.c uiciname.c

lintc:
	$(LINT) $(LOPS) client.c restart.c uici.c uiciname.c

lintcr:
	$(LINT) $(LOPS) reflectclient.c restart.c uici.c uiciname.c

lintca:
	$(LINT) $(LOPS) client_audio.c restart.c uici.c uiciname.c hasvoice.c

lintc2:
	$(LINT) $(LOPS) client2.c restart.c uici.c uiciname.c copy2files.c

lints2:
	$(LINT) $(LOPS) server2.c restart.c uici.c uiciname.c copy2files.c

clean:
	rm -f *.o server serverp serverp2 client server2 client2 client_audio reflectserver reflectclient


