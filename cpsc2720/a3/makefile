CC = g++
CCFLAGS = -Wall -g

test : test.o accountTest.o bank.o myio.o customer.o businessCustomer.o personalCustomer.o account.o chequingAccount.o savingsAccount.o chequingSavingsAccount.o
	$(CC) $(CCFLAGS) $^ -o $@ -lcppunit -ldl

%.o : %.cc
	$(CC) $(CCFLAGS) -c $<

test.o : accountTest.o
accountTest.o : accountTest.h
customer.o : customer.h
businessCustomer.o : customer.h businessCustomer.h
personalCustomer.o : customer.h personalCustomer.h
account.o : account.h customer.h personalCustomer.h businessCustomer.h
savingsAccount.o : account.h savingsAccount.h
chequingAccount.o : account.h chequingAccount.h
chequingSavingsAccount : account.h savingsAccount.h chequingAccount.h chequingSavingsAccount.h
bank.o : myio.h account.h savingsAccount.h chequingAccount.h chequingSavingsAccount.h
myio.o : myio.h

clean :
	rm -f *.o *~ #* .#*

clean-all : clean
	rm -f test
