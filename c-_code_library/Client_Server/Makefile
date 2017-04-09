# Makefile for the socket programming tutorial 
#

server = ServerSocket.o Socket.o server.o ServerSocket.h Socket.h SocketException.h
client = ClientSocket.o Socket.o client.o ServerSocket.h Socket.h SocketException.h


all : server client

server: $(server)
	g++ -o server $(server) -lpthread


client: $(client)
	g++ -o client $(client)


Socket: Socket.cpp 
ServerSocket: ServerSocket.cpp 
ClientSocket: ClientSocket.cpp
server: server.cpp
client: client.cpp


clean:
	rm -f *.o simple_server simple_client *.gch
