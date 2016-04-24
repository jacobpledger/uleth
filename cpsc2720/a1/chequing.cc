#include "chequing.h"
using namespace std;

///\post a chequingAccount is created and initialized
///\param initialize the number of free withdrawals and the withdrawal fee respectively

chequingAccount::chequingAccount(const int fw, const int wf)
{
   custptr = NULL;
   balance = 0;
   accNum = "0000000000";
   freeWithdrawals = fw;
   withdrawals = 0;
   withdrawalFee = wf;
};

///\post the account info is reinitialized

void chequingAccount::read(istream& is)
{
   account::read(is);
   is >> freeWithdrawals >> withdrawals >> withdrawalFee;
};

///\post the account info is sent to the output stream

void chequingAccount::write(ostream& os)
{
   account::write(os);
   os << freeWithdrawals << ' ' << withdrawals << ' '
      << withdrawalFee << endl;
};

///\post the number of withdrawals is reset

void chequingAccount::updateMonthEnd()
{
   withdrawals = 0;
};

///\pre balance can be negative
///\post the amount specified has been subtracted from the balance
///\param the amount to be removed from the account balance, can be negative

void chequingAccount::withdraw(const int amount)
{
   account::withdraw(amount);
   if(withdrawals > freeWithdrawals)
      account::withdraw(withdrawalFee);
};
