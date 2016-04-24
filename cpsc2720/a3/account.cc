//**********************************************************************
/// \file 
/// \brief Implementation file for the account class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 4
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <cctype>
#include <iostream>
#include <sstream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "customer.h"
#include "personalCustomer.h"
#include "businessCustomer.h"
#include "exceptions.h"

// make a copy of the data in an Account
//
/// \param orig imports the Account to make a copy of
void Account::copy(const Account& orig) {
   customerPtr = orig.customerPtr->clone();
   accountNumber = orig.accountNumber;
   balance = orig.balance;
}

// return memory to the heap
void Account::cleanUp() {
   delete customerPtr;
   customerPtr = NULL;
}

// copy constructor
//
/// \param orig imports the Account to make a copy of
Account::Account(const Account& orig) throw() { copy(orig); }

// destructor
//
/// clean up the Customer pointer
/// \post memory associated with the customer is returned to the heap
Account::~Account() throw() { cleanUp(); }

// overload the assignment operator
//
//\param orig imports the Account to be assigned
Account& Account::operator=(const Account& orig) {
   if(this != &orig) {     // avoid self-assignment
      cleanUp();  // prevent a memory leak
      copy(orig);
   }
   return *this;
}

// Reads the information for an account from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
/// throw input_format_error if input data is not correct
istream& Account::read(istream& is) throw(input_format_error) {
   char customerType;
   is >> customerType;
   Customer* tempCustomerPtr;
   switch (toupper(customerType)) {
      case 'P': tempCustomerPtr = new(PersonalCustomer); break;
      case 'B': tempCustomerPtr = new(BusinessCustomer); break;
      default : throw(input_format_error("Invalid customer type"));
   }
   try {
      is >> *tempCustomerPtr;
   }
   catch (...) {                 // catch any exception
      delete tempCustomerPtr;    // return memory to the heap
      throw;                     // and toss the exception on
   }
   
   string tempAccNumber;
   int tempBalance;
   is >> tempAccNumber >> tempBalance;
   if (!is) {
      delete tempCustomerPtr;    // return memory to the heap
      throw(input_format_error("Bad account record"));
   }
   // Have a valid account so clean up the old record and store new one;
   delete customerPtr;
   customerPtr = tempCustomerPtr;
   accountNumber = tempAccNumber;
   balance = tempBalance;
   return is;
}

// Writes the information for an account to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& Account::write(ostream& os) const  throw(){
   os << *customerPtr << accountNumber << ' ' << balance << endl;
   return os;
}

// Deposits \a amount into this account
//
/// \param [in] amount imports the amount to be deposited
/// \post the balance has been increased by amount
void  Account::deposit(int amount)  throw(){ balance += amount; }
   

// Withdraws \a amount from this account
//
/// \param [in] amount imports the amount to be withdrawn
/// \post the balance has been decreased by amount
/// \throw insufficient_funds if there is not enough money in the account
void  Account::withdraw(int amount) throw(insufficient_funds) {
   std::ostringstream message;
   if (balance < amount) {
      message << "You do not have $" << amount << " in your account";
      throw insufficient_funds(message.str());
   }
  balance -= amount;
}

// Function to return the account number
//
/// \return the account number
string  Account::getAccountNumber() const throw() { return accountNumber; }
      
// overload the extraction operator
//
// this is a non-member function
/// \param [in,out] is the stream to read from and the updated stream
/// \param [out] a the account to be extracted from the stream
/// \return the updated stream, so that it can be cascaded
/// throw input_format_error if input data is not correct
istream& operator>>(istream& is, Account& a) throw(input_format_error) {
   return a.read(is);
}

// overload the insertion operator
//
// this is a non-member function
/// \param [in,out] os the stream to read from and the updated stream
/// \param [in] a the account to be inserted into the stream
/// \return the updated stream, so that it can be cascaded
ostream& operator<<(ostream& os, const Account& a) throw() {
   return a.write(os);
}
