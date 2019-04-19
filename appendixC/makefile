CC = cc
COPS =
LINT = lint
LOPS = -x -u
NETLIBS = -lsocket -lnsl

all: client server client_r server_r client_p server_p client_m server_m client_udp server_udp

server: server.c restart.c uiciname.c uici.c
	$(CC) $(COPS) -o server server.c restart.c uiciname.c uici.c $(NETLIBS)

client: client.c restart.c uici.c 
	$(CC) $(COPS) -o client client.c restart.c uiciname.c uici.c $(NETLIBS)

server_r: server.c restart.c uiciname.c uici.c
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_R -o server_r server.c restart.c uiciname.c uici.c $(NETLIBS)

client_r: client.c restart.c uici.c 
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_R -o client_r client.c restart.c uiciname.c uici.c $(NETLIBS)

server_p: server.c restart.c uiciname.c uici.c
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_POSIX -o server_p server.c restart.c uiciname.c uici.c $(NETLIBS)

client_p: client.c restart.c uici.c 
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_POSIX -o client_p client.c restart.c uiciname.c uici.c $(NETLIBS)

server_m: server.c restart.c uiciname.c uici.c
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_MUTEX -o server_m server.c restart.c uiciname.c uici.c $(NETLIBS)

client_m: client.c restart.c uici.c 
	$(CC) $(COPS) -DREENTRANCY=REENTRANT_MUTEX -o client_m client.c restart.c uiciname.c uici.c $(NETLIBS)

server_udp: server_udp.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o server_udp server_udp.c restart.c uiciname.c uiciudp.c $(NETLIBS)

client_udp: client_udp.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o client_udp client_udp.c restart.c uiciname.c uiciudp.c $(NETLIBS)

lints:
	$(LINT) $(LOPS) server.c restart.c uiciname.c uici.c

lintc:
	$(LINT) $(LOPS) client.c restart.c uiciname.c uici.c

lints_r:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_R server.c restart.c uiciname.c uici.c

lintc_r:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_R client.c restart.c uiciname.c uici.c

lints_p:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_POSIX server.c restart.c uiciname.c uici.c

lintc_p:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_POSIX client.c restart.c uiciname.c uici.c

lints_m:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_MUTEX server.c restart.c uiciname.c uici.c

lintc_m:
	$(LINT) $(LOPS) -DREENTRANCY=REENTRANT_MUTEX client.c restart.c uiciname.c uici.c

lintus:
	$(LINT) $(LOPS) server_udp.c uiciname.c uiciudp.c

lintuc:
	$(LINT) $(LOPS) client_udp.c uiciname.c uiciudp.c


clean:
	rm -f *.o server client server_r client_r server_p client_p server_m client_m server_udp client_udp


