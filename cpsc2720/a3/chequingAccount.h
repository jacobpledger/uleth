//**********************************************************************
/// \file
/// \brief Interface file for the ChequingAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 5
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef CHEQUING_ACCOUNT_H
#define CHEQUING_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "exceptions.h"

/// A simple abstract base class to represent a ChequingAccount
class ChequingAccount : public virtual Account
{
   public:
      /// default constructor
      //
      /// \param numFree imports the number of free withdrawals allowed
      /// \param howMany imports the number of withdrawals made
      /// \param fee imports the fee to be charged for a withdrawal
      ChequingAccount(int numFree = 0, int howMany = 0, int fee = 0) throw()
	 : Account(), freeWithdrawals(numFree), withdrawals(howMany),
	   withdrawalFee(fee) {}
      
      /// Reads all information for a chequing account, from a stream
      virtual istream& read(istream& is)  throw(input_format_error);

      /// Writes all information for a chequing account, to a stream
      virtual ostream& write(ostream& os) const throw();

      /// Withdraws \a amount from this account
      virtual void withdraw(int amount) throw(insufficient_funds);

      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd() throw();

   protected:
      /// Reads the information,specific to a chequing account, from a stream
      virtual istream& readExtra(istream& is) throw(input_format_error);

      /// Writes the information, specific to a chequing account, to a stream
      virtual ostream& writeExtra(ostream& os) const throw();
      
      
   private:
      int freeWithdrawals;
      int withdrawals;
      int withdrawalFee;
};

#endif
  
