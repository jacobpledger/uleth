CCC= g++

CCCFLAGS = -Wall

all : customer.o personalCustomer.o businessCustomer.o account.o savings.o chequing.o cheqsav.o

	bank : bank.o
	$(CCC) $(CCCFLAGS) $^ -o $@

%.o : %.cc
	$(CCC) -c $(CCCFLAGS) $<

customer.o : customer.cc
personalCustomer.o : personalCustomer.cc
businessCustomer.o : businessCustomer.cc
account.o : account.cc
savings.o : savings.cc
chequing.o : chequing.cc
cheqsav.o : cheqsav.cc

clean:
	rm -f *.o *~ *% *# .#*

clean-all: clean
	rm -f bank
