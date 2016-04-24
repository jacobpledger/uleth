#include "account.h"
#include "personalCustomer.h"
#include "businessCustomer.h"
using namespace std;

///\post an "empty" account object is created and initialized

account::account()
{
   custptr = NULL;
   balance = 0;
   accNum = "0000000000";
};

///\post the account is deleted and memory is cleared

account::~account()
{
   delete custptr;
   custptr = NULL;
};

///\return the account number is returned

string account::getAccountNumber()
{
   return this->accNum;
};

///\return the account balance is returned

int account::getAccountBalance()
{
   return balance;
}

///\pre the account has been initialized
///\post the account information is sent to the output stream

void account::write(ostream& os)const
{
   os << accNum << ' ' << endl << balance << endl;
};

///\pre account info has been entered in the correct format
///\post a customer of a particular type has been created and linked to the account

void account::read(istream& is)
{
   char accType = 'N';
   is >> accType;
   if (accType == 'P')
   {
      custptr = new personalCustomer;
      personalCustomer::read(is);
   }
   else if (accType == 'B')
   {
      custptr = new businessCustomer;
      businessCustomer::read(is);
   }
};

///\param the amount to be added to the balance
///\pre the amount can be negative, no error checking
///\post the amount has been added to the account balance

void account::deposit(int amount)
{
   balance += amount;
};

///\param the amount is removed from the account balance
///\pre the amount can be negative, no error checking
///\post the amount has been subtracted from the balance

void account::withdraw(const int amount)
{
   balance -= amount;
};

///\post this does nothing here

void account::updateMonthEnd()
{};


///overloaded operators, simply call helper functions

ostream& operator<<(ostream& os, const account& acct)
{
   acct.write(os);
   return os;
};

istream& operator>>(istream& is, account& acct)
{
   acct.read(is);
   return is;
};
