#ifndef BUSINESSCUSTOMER_H
#define BUSINESSCUSTOMER_H

#include<iostream>
#include<string>

class businessCustomer : public customer
{
  public:
   businessCustomer(string = "", string = "");
   void read(istream&);
   void write(ostream&)const;
   
 
   friend class account;
   
  private:
   string name;
   string registration;
};

ostream& operator<<(ostream&, const businessCustomer&);
istream& operator>>(istream&, businessCustomer&);

#endif
