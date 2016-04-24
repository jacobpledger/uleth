//**********************************************************************
/// \file 
/// \brief Implementation file for the account class 
///
/// \author Jacob Pledger    (using Rex's solution)
/// \date Sept 24, 2009
//**********************************************************************
#include <cctype>
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "account.h"
#include "customer.h"
#include "personalCustomer.h"
#include "businessCustomer.h"

// make a copy of the data in an Account
//
/// \param orig imports the Account to make a copy of
void Account::copy(const Account& orig) {
   customerPtr = orig.customerPtr->clone();
   *customerPtr = *(orig.customerPtr);
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
Account::Account(const Account& orig) { copy(orig); }

// destructor
//
/// clean up the Customer pointer
/// \post memory associated with the customer is returned to the heap
Account::~Account() { cleanUp(); }

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
/// \exception thrown if the input does not start with a B or P or if the account number is of incorrect length
/// \return the updated stream, so that it can be cascaded
istream& Account::read(istream& is)throw(input_format_error)
{
   cleanUp();            // prevent a memory leak
   char customerType;
   is >> customerType;
   switch (toupper(customerType))
   {
      case 'P': customerPtr = new(PersonalCustomer); break;
      case 'B': customerPtr = new(BusinessCustomer); break;
      default : throw input_format_error("input must start with either a P or B");
   }
   string acctNumCheck;
   is >> *customerPtr >> acctNumCheck >> balance;
   if (acctNumCheck.length() != 7)
      throw input_format_error("invalid length of account number");
   else
      accountNumber = acctNumCheck;
   return is;
}

// Writes the information for an account to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& Account::write(ostream& os) const
{
   os << *customerPtr << accountNumber << ' ' << balance << endl;
   return os;
}

// Deposits \a amount into this account
//
/// \param [in] amount imports the amount to be deposited
/// \post the balance has been increased by amount
void  Account::deposit(int amount){balance += amount; }
   

// Withdraws \a amount from this account
//
/// \param [in] amount imports the amount to be withdrawn
/// \exception thrown if the caller trys to withdraw more than available
/// \post the balance has been decreased by amount
void  Account::withdraw(int amount)throw(insufficient_funds)
{
   try{
      if(balance < amount)
	 throw insufficient_funds("Not enough money");
      else
	 balance -= amount;
   }
   catch(insufficient_funds)
   {
      cout << "Enter an amount to withdraw (enter 0 to cancel): " << endl;
	 int amt;
      cin >> amt;
      withdraw(amt);
   };
      
}

// Function to return the account number
//
/// \return the account number
string  Account::getAccountNumber() const { return accountNumber; }
      
// overload the extraction operator
//
// this is a non-member function
/// \param [in,out] is the stream to read from and the updated stream
/// \param [out] a the account to be extracted from the stream
/// \return the updated stream, so that it can be cascaded
istream& operator>>(istream& is, Account& a) { return a.read(is); }

// overload the insertion operator
//
// this is a non-member function
/// \param [in,out] os the stream to read from and the updated stream
/// \param [in] a the account to be inserted into the stream
/// \return the updated stream, so that it can be cascaded
ostream& operator<<(ostream& os, const Account& a) { return a.write(os); }
