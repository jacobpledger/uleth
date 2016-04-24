#ifndef CHEQUING_H
#define CHEQUING_H
#include<iostream>
using namespace std;

class chequingAccount : public account
{
  public:
   chequingAccount(const int = 0, const int = 0, const int = 0);
   void read(istream&);
   void write(ostream& os);
   void updateMonthEnd();
   void withdraw(const int);
   
  private:
   int freeWithdrawals;
   int withdrawals;
   int withdrawalFee;
   
};

#endif
