#ifndef PERSONALCUSTOMER_H
#define PERSONALCUSTOMER_H

#include <iostream>
#include <string>

class personalCustomer : public customer
{
  public:
   personalCustomer(int = 0, string = "");
   void read(istream&);
   void write(ostream&)const;


   friend class account;

  private:
   string name;
   int sin;
};

ostream& operator<<(ostream&, const personalCustomer&);
istream& operator>>(istream&, personalCustomer&);

#endif
