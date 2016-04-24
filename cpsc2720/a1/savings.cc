#include "savings.h"
using namespace std;

///\post a savingsAccount is created and initialized

savingsAccount::savingsAccount()
{
   custptr = NULL;
   balance = 0;
   accNum = "0000000000"
   interestRate = 0;
};

///\post the savingsAccount info is reinitialized

void savingsAccount::read(istream& is)
{
   account::read(is);
   readExtra(is);
};

///\post the account info is sent to the output stream

void savingsAccount::write(ostream& os)
{
   account::write(os);
   writeExtra(os);
};

///helper function for ease of inheritence

void savingsAccount::readExtra(istream& is)
{
   is >> interestRate;
};

///helper function for ease of inheritence

void savingsAccount::writeExtra(ostream& os)
{
   os << interestRate << endl;
};

///\post adds the interest rate to the balance

void savingsAccount::updateMonthEnd()
{
   int b = getAccountBalance();
   b *= interestRate;
   b -= getAccountBalance();
   deposit(b);
};

