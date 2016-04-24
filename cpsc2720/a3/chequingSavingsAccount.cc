//**********************************************************************
/// \file
/// \brief Implementation file for the ChequingSavingsAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 7
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "savingsAccount.h"
#include "chequingAccount.h"
#include "chequingSavingsAccount.h"
#include "exceptions.h"

// Reads all information for a chequing savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& ChequingSavingsAccount::read(istream& is)  throw(input_format_error) {
   ChequingSavingsAccount temp;
   temp.Account::read(is);
   temp.SavingsAccount::readExtra(is);
   temp.ChequingAccount::readExtra(is);
   *this = temp;
   return is;
}

// Writes all information for a chequing savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingSavingsAccount::write(ostream& os) const throw() {
   Account::write(os);
   SavingsAccount::writeExtra(os);
   return ChequingAccount::writeExtra(os);
}

// Performs updates to the account at the end of the month
//
/// \post Interest earned has been added to the balance
/// \post The number of withdrawals is reset to 0
void ChequingSavingsAccount::updateMonthEnd() throw() {
   SavingsAccount::updateMonthEnd();
   ChequingAccount::updateMonthEnd();
}

