.c.o:
	gcc -c -Wall $<

all: simp.h client server

simp_xdr.c: simp.h

client: simp.h simp_clnt.o simp_xdr.o simpclient.o
	gcc -o client simpclient.o simp_clnt.o simp_xdr.o

simp_clnt.c: simp.h

server: simp.h simpservice.o simp_svc.o simp_xdr.o
	gcc -o server simpservice.o simp_svc.o simp_xdr.o

simp_svc.c: simp.h

simp.h: simp.x
	rpcgen -C simp.x

clean: 
	rm -f simp.h simp_svc.* simp_clnt.* simp_xdr.* *.o

