//**********************************************************************
/// \file
/// \brief Implementation file for the SavingsAccount class 
///
/// \author Jacob Pledger
/// \date Nov 6, 2009
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "savingsAccount.h"

// Reads all information for a savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \exception thrown when the input cannot be correctly interpreted
/// \return the updated stream, so that it can be cascaded
istream& SavingsAccount::read(istream& is)throw(input_format_error)
{
   Account::read(is);
   return readExtra(is);
}

// Writes all information for a savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& SavingsAccount::write(ostream& os) const {
   Account::write(os);
   return writeExtra(os);
}

// Adds the interest earned to the balance at the end of the month
//
/// This function will calculate and add the interest earned to the
/// balance at the end of the month.
///
/// \post the balance is increased by the amount of interest earned
void SavingsAccount::updateMonthEnd() {
   balance += static_cast<int>(balance*(interestRate/100));
}

// Reads the information,specific to savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& SavingsAccount::readExtra(istream& is) {
   //not sure how to check for invalid inputs here
   //need to revise to ensure user does not enter garbate
   //such as alphabetic characters
   return is >> interestRate;
}

// Writes the information, specific to a savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& SavingsAccount::writeExtra(ostream& os) const {
   return os << interestRate << endl;
}
