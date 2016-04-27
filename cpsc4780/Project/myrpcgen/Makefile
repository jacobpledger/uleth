CXX	:= g++
CXXFLAGS := -g -Wall
COBJECTS	:= interface_client.o interface_clnt.o myrpcsvc.o Socket.o myrpc.o myxdr.o
SOBJECTS	:= interface_server.o interface_svc.o myrpcsvc.o Socket.o myrpc.o myxdr.o

all: client server


myrpcsvc.o: myrpcsvc.cpp
	$(CXX) $(CXXFLAGS) -c myrpcsvc.cpp -o myrpcsvc.o

Socket.o: Socket.cpp
	$(CXX) $(CXXFLAGS) -c Socket.cpp -o Socket.o

myrpc.o: myrpc.cpp
	$(CXX) $(CXXFLAGS) -c myrpc.cpp -o myrpc.o

myxdr.o: myxdr.cpp
	$(CXX) $(CXXFLAGS) -c myxdr.cpp -o myxdr.o



client: $(COBJECTS)
	$(CXX) $(COBJECTS) -o client

interface_client.o: interface_client.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c interface_client.cpp -o interface_client.o

interface_clnt.o: interface_clnt.cpp
	$(CXX) $(CXXFLAGS) -c interface_clnt.cpp -o interface_clnt.o



server: $(SOBJECTS)
	$(CXX) $(SOBJECTS) -o server

interface_server.o: interface_server.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c interface_server.cpp -o interface_server.o

interface_svc.o: interface_svc.cpp
	$(CXX) $(CXXFLAGS) -c interface_svc.cpp -o interface_svc.o


clean: 
	rm -f *.o *~
c: 
	rm -f *.o *~