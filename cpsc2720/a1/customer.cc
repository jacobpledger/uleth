#include "customer.h"
using namespace std;

customer::~customer()
{};

///overloaded operators

ostream& operator<<(ostream& os, const customer& cust)
{
   return os;
};

istream& operator>>(istream& is, customer& cust)
{
   return is;
};



