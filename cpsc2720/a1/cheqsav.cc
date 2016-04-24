#include "cheqsav.h"
using namespace std;

///\post creates and initializes a chequingSavingsAccount

chequingSavingsAccount::chequingSavingsAccount()
{
   custptr = NULL;
   balance = 0;
   accNum = "0000000000";
   interestRate = 0;
   withdrawals = 0;
   freeWithdrawals = 0;
   withdrawalFee = 0;
};

///\post reinitializes the data members of a chequingSavingsAccount

void chequingSavingsAccount::read(istream& is)
{
   account::read(is);
   is >> interestRate
      >>freeWithdrawals >> withdrawals >> withdrawalFee;
};

///\pre the account has been initialized
///\post the account info has been sent to the output stream

void chequingSavingsAccount::write(ostream& os)
{
   account::write(os);
   os << interestRate << endl
      << freeWithdrawals << withdrawals << withdrawalFee
      << endl;
};
