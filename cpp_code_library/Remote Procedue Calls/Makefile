.c.o:
	gcc -c -Wall $<

all: BIC.h client server

simp_xdr.c: BIC.h

client: BIC.h simp_clnt.o simp_xdr.o simpclient.o
	gcc -o client simpclient.o simp_clnt.o simp_xdr.o

simp_clnt.c: BIC.h

server: BIC.h simpservice.o simp_svc.o simp_xdr.o
	gcc -o server simpservice.o simp_svc.o simp_xdr.o

simp_svc.c: BIC.h

BIC.h: BIC.x
	rpcgen -C BIC.x

clean: 
	rm -f BIC.h simp_svc.* simp_clnt.* simp_xdr.* *.o

