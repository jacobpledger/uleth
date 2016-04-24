CFLAGS = -Wall -g

main: main.o quinemccluskey.o
	g++ $(CFLAGS) main.o quinemccluskey.o -o quinemccluskey

main.o: main.cpp quinemccluskey.o
	g++ $(CFLAGS) -c main.cpp

quinemccluskey.o: quinemccluskey.cpp quinemccluskey.h templates.h
	g++ $(CFLAGS) -c quinemccluskey.cpp

