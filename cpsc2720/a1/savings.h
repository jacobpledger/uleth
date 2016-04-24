#ifndef SAVINGS_H
#define SAVINGS_H
#include<iostream>

class savingsAccount : public account
{
  public:
   savingsAccount();
   void read(istream&);
   void write(ostream&);
   void updateMonthEnd();
   
  private:
   double interestRate;

  protected:
   void readExtra(istream&);
   void writeExtra(ostream&);
};

#endif
