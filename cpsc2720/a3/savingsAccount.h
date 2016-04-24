//**********************************************************************
/// \file
/// \brief Interface file for the SavingsAccount class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 5
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "exceptions.h"

/// A simple abstract base class to represent a SavingsAccount
class SavingsAccount : public virtual Account
{
   public:
      /// default constructor
      //
      /// Create a savings account with the specified interest rate
      ///
      /// \param rate imports the monthly interest rate as a percentage
   SavingsAccount(double rate = 0.0) throw() : Account(), interestRate(rate) {}
      
      /// Reads all information for a savings account, from a stream
      virtual istream& read(istream& is) throw(input_format_error);

      /// Writes all information for a savings account, to a stream
      virtual ostream& write(ostream& os) const throw();

      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd() throw();

   protected:
      /// Reads the information,specific to savings account, from a stream
      virtual istream& readExtra(istream& is) throw(input_format_error);

      /// Writes the information, specific to a savings account, to a stream
      virtual ostream& writeExtra(ostream& os) const throw();

      double interestRate;  ///< The monthly interest rate as a percentage
};

#endif
  
