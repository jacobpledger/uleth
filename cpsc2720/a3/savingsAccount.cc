//**********************************************************************
/// \file
/// \brief Implementation file for the SavingsAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 5
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "savingsAccount.h"
#include "exceptions.h"

// Reads all information for a savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& SavingsAccount::read(istream& is)  throw(input_format_error) {
   SavingsAccount temp;
   temp.Account::read(is);
   temp.readExtra(is);
   *this = temp;
   return is;
}

// Writes all information for a savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& SavingsAccount::write(ostream& os) const throw() {
   Account::write(os);
   return writeExtra(os);
}

// Adds the interest earned to the balance at the end of the month
//
/// This function will calculate and add the interest earned to the
/// balance at the end of the month.
///
/// \post the balance is increased by the amount of interest earned
void SavingsAccount::updateMonthEnd() throw() {
   balance += static_cast<int>(balance*(interestRate/100));
}

// Reads the information,specific to savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
istream& SavingsAccount::readExtra(istream& is)  throw(input_format_error) {
   is >> interestRate;
   if (!is) throw (input_format_error("Bad or missing interest rate"));
   return is;
}

// Writes the information, specific to a savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& SavingsAccount::writeExtra(ostream& os) const  throw(){
   return os << interestRate << endl;
}
