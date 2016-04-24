#include "businessCustomer.h"
using namespace std;

///\post a businessCustomer object is created and initialized
///\param initialize the name and registration of the customer

businessCustomer::businessCustomer(string a, string n)
{
   name = n;
   registration = a;
};

///\pre the businessCustomer has been initialized
///\post the data has been sent to the output stream

void businessCustomer::write(ostream& os)const
{
   os << "B " << registration << ' ' << name << endl;
};

///\post the businessCustomer has been reinitialized

void businessCustomer::read(istream& is)
{
   is >> registration >> name;
};


///overloaded operators, call helper functions

ostream& operator<<(ostream& os, const businessCustomer& bcust)
{
   bcust.write(os);
   return os;
};

istream& operator>>(istream& is, businessCustomer& bcust)
{
   bcust.read(is);
   return is;
};
