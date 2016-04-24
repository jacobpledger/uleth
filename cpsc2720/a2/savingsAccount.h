//**********************************************************************
/// \file
/// \brief Interface file for the SavingsAccount class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6 2009
//**********************************************************************
#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"

/// A simple abstract base class to represent a SavingsAccount
class SavingsAccount : public virtual Account
{
  public:
   /// default constructor
   //
   /// Create a savings account with the specified interest rate
   ///
   /// \param rate imports the monthly interest rate as a percentage
   SavingsAccount(double rate = 0.0) : Account(), interestRate(rate) {}
      
      /// Reads all information for a savings account, from a stream
      virtual istream& read(istream& is)throw(input_format_error);
      
      /// Writes all information for a savings account, to a stream
      virtual ostream& write(ostream& os) const;
      
      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd();
      
  protected:
      /// Reads the information,specific to savings account, from a stream
      virtual istream& readExtra(istream& is);
      
      /// Writes the information, specific to a savings account, to a stream
      virtual ostream& writeExtra(ostream& os) const;
      
      double interestRate;  ///< The monthly interest rate as a percentage
};

#endif
  
