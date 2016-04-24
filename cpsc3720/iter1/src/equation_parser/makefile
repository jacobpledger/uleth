CFLAGS = -Wall -g

main: main.o expressionparser.o expressiontoken.o
	g++ $(CFLAGS) main.o expressionparser.o expressiontoken.o -o main

main.o: main.cpp expressionparser.o
	g++ $(CFLAGS) -c main.cpp

expressionparser.o: expressionparser.cpp expressionparser.h expressiontoken.o
	g++ $(CFLAGS) -c expressionparser.cpp

expressiontoken.o: expressiontoken.cpp expressiontoken.h
	g++ $(CFLAGS) -c expressiontoken.cpp

