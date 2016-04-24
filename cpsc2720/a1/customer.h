#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
using namespace std;

class customer
{
  public:
   virtual ~customer();
   virtual void read(istream&) = 0;
   virtual void write(ostream&)const = 0;


   friend class account;
};

istream& operator>>(istream&, customer&);
ostream& operator<<(ostream&, const customer&);

#endif
