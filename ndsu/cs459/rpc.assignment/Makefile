CC=/usr/bin/cc
RPCGEN=/usr/bin/rpcgen
APPN=date
LIBS=-lrpc

all: rdate $(APPN)_svc

rdate: $(APPN)_clnt.c $(APPN).h rdate.c
	$(CC) -o rdate $(APPN)_clnt.c rdate.c $(LIBS)

$(APPN)_svc: $(APPN)_svc.c $(APPN).h $(APPN)_proc.c
	$(CC) -o $(APPN)_svc $(APPN)_proc.c $(APPN)_svc.c $(LIBS)

#stubs
$(APPN)_svc.c $(APPN).h $(APPN)_clnt.c: $(APPN).x
	$(RPCGEN) $(APPN).x

clean:
	rm -f *.o rdate $(APPN)_svc

spotless:
	rm -f *.o rdate $(APPN)_svc $(APPN)_svc.c $(APPN)_clnt.c $(APPN).h
