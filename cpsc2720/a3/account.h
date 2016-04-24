//**********************************************************************
/// \file
/// \brief Interface file for the account class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 4
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

using std::istream;
using std::ostream;
using std::string;

#include "customer.h"
#include "exceptions.h"

/// A simple abstract base class to represent an Account
class Account
{
   public:
      /// default constructor
      //
      /// creates an account with a 0 balance and no customer
      Account() throw():customerPtr(NULL), accountNumber("00000"), balance(0){}

      /// copy constructor
      Account(const Account&) throw();
      
      /// Destructor; virtual so that sub class objects are correctly destroyed
      virtual ~Account() throw();

      /// Overload the assignment operator
      Account& operator=(const Account&);

      /// Reads the information for an account from a stream
      virtual istream& read(istream& is) throw(input_format_error);

      /// Writes the information for an account to a stream
      //
      /// \param [in,out] os the stream to write to and the updated stream
      /// \return the updated stream, so that it can be cascaded
      virtual ostream& write(ostream& os) const throw();

      /// Deposits \a amount into this account
      //
      /// \param [in] amount imports the amount to be deposited
      virtual void deposit(int amount) throw();

      /// Withdraws \a amount from this account
      //
      /// \param [in] amount imports the amount to be withdrawn
      virtual void withdraw(int amount) throw(insufficient_funds);

      /// Performs updates to the account at the end of the month
      virtual void updateMonthEnd() throw() = 0;

      /// Returns the account number
      string getAccountNumber() const throw();

   private:
      Customer* customerPtr;   ///< A pointer to a customer record
      string accountNumber;    ///< The account number

      void copy(const Account&); ///< make a copy of the data for Account
      void cleanUp();            ///< return memory to the heap
      
   protected:
      int balance;             ///< The balance in this account
};

/// overload the extraction operator
//
// this is a non-member function
istream& operator>>(istream& is, Account& a) throw(input_format_error);

/// overload the insertion operator
//
// this is a non-member function
ostream& operator<<(ostream& os, const Account& a) throw();
   
#endif
  
