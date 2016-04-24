//**********************************************************************
/// \file
/// \brief Interface file for the ChequingSavingsAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 7
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef CHEQUING_SAVINGS_ACCOUNT_H
#define CHEQUING_SAVINGS_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "savingsAccount.h"
#include "chequingAccount.h"
#include "exceptions.h"

/// A concrete derived class to represent a ChequingSavingsAccount
class ChequingSavingsAccount
   : public virtual ChequingAccount, public virtual SavingsAccount
{
   public:
      /// default constructor
      //
      /// \param rate imports the monthly interest rate as a percentage
      /// \param numFree imports the number of free withdrawals allowed
      /// \param howMany imports the number of withdrawals made
      /// \param fee imports the fee to be charged for a withdrawal
      ChequingSavingsAccount(double rate = 0.0,
			     int numFree = 0, int howMany = 0, int fee = 0)
	                     throw()
	 : Account (),
	   ChequingAccount(numFree, howMany, fee),
	   SavingsAccount(rate) { }
      
      /// Reads all information for a chequing savings account, from a stream
      virtual istream& read(istream& is) throw(input_format_error);

      /// Writes all information for a chequing savings account, to a stream
      virtual ostream& write(ostream& os) const throw();

      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd() throw();

};
#endif
