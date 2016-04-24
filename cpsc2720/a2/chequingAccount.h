//**********************************************************************
/// \file
/// \brief Interface file for the ChequingAccount class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#ifndef CHEQUING_ACCOUNT_H
#define CHEQUING_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"

/// A simple abstract base class to represent a ChequingAccount
class ChequingAccount : public virtual Account
{
   public:
   /// default constructor
   //
   /// \param numFree imports the number of free withdrawals allowed
   /// \param howMany imports the number of withdrawals made
   /// \param fee imports the fee to be charged for a withdrawal
   ChequingAccount(int numFree = 0, int howMany = 0, int fee = 0)
      : Account(), freeWithdrawals(numFree), withdrawals(howMany),
      withdrawalFee(fee) {}
      
      /// Reads all information for a chequing account, from a stream
      virtual istream& read(istream& is)throw(input_format_error);
      
      /// Writes all information for a chequing account, to a stream
      virtual ostream& write(ostream& os) const;
      
      /// Withdraws \a amount from this account
      virtual void withdraw(int amount)throw(insufficient_funds);
      
      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd();
      
  protected:
      /// Reads the information,specific to a chequing account, from a stream
      virtual istream& readExtra(istream& is);
      
      /// Writes the information, specific to a chequing account, to a stream
      virtual ostream& writeExtra(ostream& os) const;
      
      
  private:
      int freeWithdrawals;
      int withdrawals;
      int withdrawalFee;
};

#endif
  
