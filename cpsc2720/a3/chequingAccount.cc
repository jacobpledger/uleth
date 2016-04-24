//**********************************************************************
/// \file
/// \brief Implementation file for the ChequingAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 5
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
#include <sstream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "chequingAccount.h"
#include "exceptions.h"

// Reads all information for a chequing account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& ChequingAccount::read(istream& is) throw(input_format_error) {
   ChequingAccount temp;
   temp.Account::read(is);
   temp.readExtra(is);
   *this = temp;
   return is;
}

// Writes all information for a chequing account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingAccount::write(ostream& os) const  throw(){
   Account::write(os);
   return writeExtra(os);
}

// Reads the information,specific to a chequing account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& ChequingAccount::readExtra(istream& is)  throw(input_format_error) {
   is >> freeWithdrawals >> withdrawals >> withdrawalFee;
   if (!is)
      throw (input_format_error("Bad or missing withdrawal fee information"));
   return is;
}

// Writes the information, specific to a chequing account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingAccount::writeExtra(ostream& os) const throw() {
   return os << freeWithdrawals << ' ' << withdrawals << ' ' << withdrawalFee
								<< endl;
}

// Withdraws \a amount from this account
//
/// \param [in] amount imports the amount to be withdrawn
/// \post the balance has been increased by amount plus any service charges
void ChequingAccount::withdraw(int amount) throw(insufficient_funds) {
   std::ostringstream message;
   if (balance < amount) {
      message << "You do not have $" << amount << " in your account";
      throw insufficient_funds(message.str());
   }
   balance -= amount;
   withdrawals++;
   if (withdrawals > freeWithdrawals) balance -= withdrawalFee;
}

// Performs updates to the account at the end of the month
//
/// \post the number of withdrawals has been set to 0
void ChequingAccount::updateMonthEnd()  throw() {
   withdrawals = 0;
}
  
