.c.o:
	gcc -c -Wall $<

all: BIC.h client server

BIC_xdr.c: BIC.h

client: BIC.h BIC_clnt.o BIC_xdr.o BICClientImpl.o
	gcc -o client BICClientImpl.o BIC_clnt.o BIC_xdr.o

BIC_clnt.c: BIC.h

server: BIC.h BICServerImpl.o BIC_svc.o BIC_xdr.o
	gcc -o server BICServerImpl.o BIC_svc.o BIC_xdr.o

BIC_svc.c: BIC.h

BIC.h: BIC.x
	rpcgen -C BIC.x

clean: 
	rm -f BIC.h BIC_svc.* BIC_clnt.* BIC_xdr.* *.o

