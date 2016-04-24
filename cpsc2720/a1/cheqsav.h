#ifndef CHEQSASV_H
#define CHEQSAV_H

#include <iostream>
using namespace std;

class chequingSavingsAccount: public chequingAccount, public savingsAccount
{
   chequingSavingsAccount();
   void read(istream&);
   void write(ostream&);
};

#endif
