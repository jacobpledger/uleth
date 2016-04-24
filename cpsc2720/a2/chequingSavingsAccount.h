//**********************************************************************
/// \file
/// \brief Interface file for the ChequingSavingsAccount class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#ifndef CHEQUING_SAVINGS_ACCOUNT_H
#define CHEQUING_SAVINGS_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "savingsAccount.h"
#include "chequingAccount.h"

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
	 : Account (),
	   ChequingAccount(numFree, howMany, fee),
	   SavingsAccount(rate) { }
      
	 /// Reads all information for a chequing savings account, from a stream
	 virtual istream& read(istream& is)throw(input_format_error);
	 
	 /// Writes all information for a chequing savings account, to a stream
	 virtual ostream& write(ostream& os) const;
	 
	 /// Performs updates to the account at the end of the month
	 virtual void updateMonthEnd();
	 
};
#endif
