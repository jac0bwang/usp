CC = cc
COPS =
LINT = lint
LOPS = -x -u
NETLIBS = -lsocket -lnsl

all: server_udp client_udp server_udp_request_reply client_udp_request_reply client_udp_request_reply_timeout client_udp_request_reply_timeout_retry multicast_receiver sender_udp multicast_rectest

server_udp: server_udp.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o server_udp server_udp.c restart.c uiciname.c uiciudp.c $(NETLIBS)

server_udp_request_reply: server_udp_request_reply.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o server_udp_request_reply server_udp_request_reply.c restart.c uiciname.c uiciudp.c $(NETLIBS)

client_udp: client_udp.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o client_udp client_udp.c restart.c uiciname.c uiciudp.c $(NETLIBS)

client_udp_request_reply: client_udp_request_reply.c request_reply.c restart.c uiciudp.c
	$(CC) $(COPS) -o client_udp_request_reply client_udp_request_reply.c request_reply.c restart.c uiciname.c uiciudp.c $(NETLIBS)

client_udp_request_reply_timeout: client_udp_request_reply_timeout.c request_reply_timeout.c restart.c uiciudp.c
	$(CC) $(COPS) -o client_udp_request_reply_timeout client_udp_request_reply_timeout.c request_reply_timeout.c restart.c uiciname.c uiciudp.c $(NETLIBS)

client_udp_request_reply_timeout_retry: client_udp_request_reply_timeout_retry.c request_reply_timeout_retry.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o client_udp_request_reply_timeout_retry client_udp_request_reply_timeout_retry.c request_reply_timeout_retry.c restart.c uiciname.c uiciudp.c $(NETLIBS)

sender_udp: sender_udp.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o sender_udp sender_udp.c restart.c uiciname.c uiciudp.c $(NETLIBS)

multicast_receiver: multicast_receiver.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o multicast_receiver multicast_receiver.c restart.c uiciname.c uiciudp.c $(NETLIBS)

multicast_rectest: multicast_rectest.c restart.c uiciname.c uiciudp.c
	$(CC) $(COPS) -o multicast_rectest multicast_rectest.c uiciname.c restart.c uiciudp.c $(NETLIBS)

lintall: lintsu1 lintsrr lintc lintcrr lintcrrt lintcrrtr lintmr lintmrt lints lintcomparehost lintgethostinfo lintgethostname lintjoin lintleave lintrecvfromtimed lintopenudp lintrecvfrom lintsendto lintputblock

lintsu1:
	$(LINT) $(LOPS) server_udp.c uiciname.c uiciudp.c

lintsrr:
	$(LINT) $(LOPS) server_udp_request_reply.c uiciname.c uiciudp.c

lintc:
	$(LINT) $(LOPS) client_udp.c uiciname.c uiciudp.c

lintcrr:
	$(LINT) $(LOPS) client_udp_request_reply.c request_reply.c uiciname.c uiciudp.c

lintcrrt:
	$(LINT) $(LOPS) client_udp_request_reply_timeout.c request_reply_timeout.c uiciname.c uiciudp.c

lintcrrtr:
	$(LINT) $(LOPS) client_udp_request_reply_timeout_retry.c request_reply_timeout_retry.c uiciname.c uiciudp.c

lintmr:
	$(LINT) $(LOPS) multicast_receiver.c uiciudp.c

lintmrt:
	$(LINT) $(LOPS) multicast_rectest.c uiciudp.c

lints:
	$(LINT) $(LOPS) sender_udp.c uiciname.c uiciudp.c

lintcomparehost:
	$(LINT) $(LOPS) u_comparehost.c

lintgethostinfo:
	$(LINT) $(LOPS) u_gethostinfo.c

lintgethostname:
	$(LINT) $(LOPS) u_gethostname.c

lintjoin:
	$(LINT) $(LOPS) u_join.c

lintleave:
	$(LINT) $(LOPS) u_leave.c

lintrecvfromtimed:
	$(LINT) $(LOPS) u_recvfromtimed.c

lintopenudp:
	$(LINT) $(LOPS) u_openudp.c

lintrecvfrom:
	$(LINT) $(LOPS) u_recvfrom.c

lintsendto:
	$(LINT) $(LOPS) u_sendto.c

lintputblock:
	$(LINT) $(LOPS) putblock.c


runrec:
	multicast_receiver 224.0.0.10 16001

runsend:
	sender_udp 224.0.0.10 16001

runsend1:
	sender_udp 239.255.0.1 16002

runrec1:
	multicast_receiver 239.255.0.1 16002

runrect:
	multicast_rectest 239.255.0.1 16002

clean:
	rm -f *.o server_udp client_udp server_udp_request_reply client_udp_request_reply client_udp_request_reply_timeout multicast_receiver sender_udp multicast_rectest client_udp_request_reply_2 client_udp_request_reply_timeout_retry


