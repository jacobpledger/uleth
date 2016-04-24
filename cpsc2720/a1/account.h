#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class account
{
  public:
   account();
   ~account();
   virtual void read(istream&);
   virtual void write(ostream&)const;
   string getAccountNumber();
   int getAccountBalance();
   virtual void deposit(int amount);
   virtual void withdraw(const int amount);
   virtual void updateMonthEnd();

  friend class customer;
   
  private:
   customer* custptr;
   string accNum;
   int balance;
   
};

ostream& operator<<(ostream&, const account&);
istream& operator>>(istream&, account&);

#endif
