#include "personalCustomer.h"
using namespace std;

///\param initialize the name and SIN
///\post a personalCustomer object is created

personalCustomer::personalCustomer(int s, string n)
{
   sin = s;
   name = n;
};

///\param reinitialize the name and SIN for a personalCustomer
///\post the personalCustomer's name and SIN have been re-initialized from an input

void personalCustomer::read(istream& is)
{
   is >> sin >> name;
};

///\pre the personalCustomer has been initialized
///\post personalCustomer info is sent to the output stream

void personalCustomer::write(ostream& os)const
{
   os << "P " << sin << ' ' << name << endl;
};


///overloaded operators, call helper functions

ostream& operator<<(ostream& os, const personalCustomer& pcust)
{
   pcust.write(os);
   return os;
};

istream& operator>>(istream& is, personalCustomer& pcust)
{
   pcust.read(is);
   return is;
};
