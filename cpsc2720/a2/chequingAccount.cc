//**********************************************************************
/// \file
/// \brief Implementation file for the ChequingAccount class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "chequingAccount.h"

// Reads all information for a chequing account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \exception thrown from account::read()
/// \return the updated stream, so that it can be cascaded
istream& ChequingAccount::read(istream& is)throw(input_format_error)
{
   Account::read(is);
   return readExtra(is);
}

// Writes all information for a chequing account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingAccount::write(ostream& os) const {
   Account::write(os);
   return writeExtra(os);
}

// Reads the information,specific to a chequing account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& ChequingAccount::readExtra(istream& is){
   //not sure how to check for invalid inputs here
   //need to revise to ensure user does not enter garbate
   //such as alphabetic characters
   
   return is >> freeWithdrawals >> withdrawals >> withdrawalFee;
}

// Writes the information, specific to a chequing account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingAccount::writeExtra(ostream& os) const {
   return os << freeWithdrawals << ' ' << withdrawals << ' ' << withdrawalFee
								<< endl;
}

// Withdraws \a amount from this account
//
/// \param [in] amount imports the amount to be withdrawn
/// \exception thrown if the balance is less than the desired amount
/// \post the balance has been increased by amount plus any service charges
void ChequingAccount::withdraw(int amount)throw(insufficient_funds)
{
   try{
      if (balance < amount)
      {
	 throw insufficient_funds("Not enough money!");
      }
      balance -= amount;
      withdrawals++;
      if (withdrawals > freeWithdrawals) balance -= withdrawalFee;
   }
   catch(insufficient_funds)
   {
      cout << "Your current balance is: " << balance << ' '
	   << "Would you like to withdraw a smaller amount?" << endl;
      cin >> amount;
   }
}

// Performs updates to the account at the end of the month
//
/// \post the number of withdrawals has been set to 0
void ChequingAccount::updateMonthEnd() {
   withdrawals = 0;
}
  
