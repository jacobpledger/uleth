//**********************************************************************
/// \file
/// \brief Client test program to test the account class hierarchy.
///
/// It reads various types of accounts into a list from a file and allows
/// you to print the entire list of accounts, deposit money to an account,
/// withdraw money from an account and perform end of month updates.
/// All these operations are done polymorphically.
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 8
/// \author Rex Forsyth
/// \date Sept 28, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "account.h"
#include "savingsAccount.h"
#include "chequingAccount.h"
#include "chequingSavingsAccount.h"
#include "myio.h"
#include "exceptions.h"

/// fill the list of accounts by reading data from a file
void fill(vector<Account*>&) throw(invalid_file, input_format_error);

/// withdraw money from an account
void withdraw(const vector<Account*>&)
                                  throw(insufficient_funds, account_not_found);

/// deposit money to an account
void deposit(const vector<Account*>&) throw(account_not_found);

/// perform end of month updates on all accounts
void update(const vector<Account*>&) throw();

/// Polymorphically print each account in the list
void print(const vector<Account*>& list) throw();

/// Remove all items from the list
void clear(vector<Account*>& list) throw();

/// find the index of the account which has this account number
int find(const vector<Account*>& accts, const string& number)
                                                      throw(account_not_found);

/// print a list of available options.
void printMenu() throw();

/// the main function for the testing program
int main()
{
   vector<Account*> accounts;
   for (;;) {
      try {
	 fill(accounts);
	 break;   // successful so exit the loop
      }
      catch (invalid_file& ex) {
	 cout << ex.what() << "!!! Try again." << endl;
      }
      catch (input_format_error& ex) {
	 cout << "Corrupt data found in file.  " << ex.what();
	 cout << "!!! Try a different file." << endl;
	 accounts.clear();  // clear out any data that was read
      }
   }
      
   char toDo;
   printMenu();
   do {
      try{
      cout << "What now (LWDUQ)? ";
      cin >> toDo;
      clrStream();    // get rid of any garbage including the new line
      switch (toupper(toDo)) {
	 case 'L': print(accounts); break;
	 case 'W':
	    for(;;) {
	       try {
		  withdraw(accounts); break;
	       }
	       catch(account_not_found& ex) {
		  cout << ex.what() << "!!!  Try again. " << endl;
	       }
	       catch (insufficient_funds& ex){
		  cout << ex.what() << "!!!  Try again. " << endl;
	       }
	    }
	    break;
	 case 'D':
	    for(;;) {
	       try {
		  deposit(accounts); break;
	       }
	       catch(account_not_found& ex) {
		  cout << ex.what() << "!!!  Try again. " << endl;
	       }
	    }   
	    break;
	 case 'U': update(accounts); break;
	 case 'Q': break ;
	 default: throw(invalid_menu_choice("Invalid choice"));
      }
      }
      catch(invalid_menu_choice& ex) {
	 cout << ex.what() << " ";
	 printMenu();
      }
   } while (toupper(toDo) != 'Q');
   
   clear(accounts);
   
   return 0;
}

// fill the list of accounts by reading data from a file
//
/// \param [out] accounts exports the list of accounts
///
/// \pre the list is empty
//
// I have chosen to overwrite any accounts that are already in the list.
// If you want to append instead of overwrite, then comment out the "clear"
// function call.
void fill(vector<Account*>& accounts) throw(invalid_file, input_format_error) {
   string filename;
   ifstream acctFile;

   cout << "Enter the name of the file which holds the account data -- ";
   getline(cin,filename);
   openIn(acctFile,filename);

   string code;
   clear(accounts);  // comment this line to append rather than overwrite
   int numAccounts = accounts.size();
   while (acctFile >> code) {
      if (code == "C") accounts.push_back(new ChequingAccount);
      else if (code == "S") accounts.push_back(new SavingsAccount);
      else if (code == "CS") accounts.push_back(new ChequingSavingsAccount);
      else throw input_format_error("Invalid account type");
      acctFile >> *accounts[numAccounts++];
   }
}

// Polymorphically print each account in the list
//
/// \param [in] accounts imports the list of accounts to print
void print(const vector<Account*>& accounts) throw(){
   int numAccounts = accounts.size();
   cout << "Here are the accounts:" << endl;
   for (int i = 0; i < numAccounts; i++)
      cout << *accounts[i] << endl;
}

// Remove all items from the list
//
/// \param [in,out] list imports the list to be cleared and
///                      exports the emptied list
/// \post the list will be empty i.e. list.size() = 0
void clear(vector<Account*>& list) throw() {
   int numItems = list.size();
   for (int i = 0; i < numItems; i++) {
      delete list[i];
   }
   list.clear();
}


// Withdraw money from an account
//
/// \param [in] accounts imports the list of accounts
/// \post the balance will be decreased
/// \throw account_not_found if an invalid account number is entered
/// \throw insufficient_funds if there is not enough money in the account
void withdraw(const vector<Account*>& accounts)
                               throw(account_not_found, insufficient_funds) {
   string number;
   cout << "Enter the account number -- ";
   cin >> number;

   int amount;
   cout << "Enter the amount to withdraw -- ";
   cin >> amount;
   
   accounts[find(accounts,number)]->withdraw(amount);
}

// Deposit money to an account
//
/// \param [in] accounts imports the list of accounts 
/// \post the balance will be increased
/// \throw account_not_found if an invalid account number is entered
void deposit(const vector<Account*>& accounts)  throw(account_not_found) {
   string number;
   cout << "Enter the account number -- ";
   cin >> number;

   int amount;
   cout << "Enter the amount to deposit -- ";
   cin >> amount;
   
   accounts[find(accounts,number)]->deposit(amount);
}

// Perform end of month updates on all accounts
//
/// \param [in] accounts imports the list of accounts 
void update(const vector<Account*>& accounts) throw() {
   int numAccounts = accounts.size();
   for (int i = 0; i < numAccounts; i++)
      accounts[i]->updateMonthEnd();
}

// find the index of the account which has this account number
//
/// \param  [in] accounts imports the list of accounts
/// \param [in] number imports the account number to search for
/// \return the index of the account number
/// \throw account_not_found if the account number does not exist.
int find(const vector<Account*>& accounts, const string& number)
                                                    throw(account_not_found) {
   
   int numAccounts = accounts.size();
   for (int i=0; i < numAccounts; i++) {
      if (accounts[i]->getAccountNumber() == number) return i;
   }
   std::ostringstream message;
   message << "Account #" << number << " does not exist!!";
   throw(account_not_found(message.str()));
}

// print a list of available options
void printMenu() throw() {
   cout << "Choose one of the following options:" << endl;
   cout << "   (L)ist the accounts and all their data." << endl;
   cout << "   (D)eposit to an account. " << endl;
   cout << "   (W)ithdraw from an account." << endl;
   cout << "   (U)pdate all accounts for end of month. " << endl;
   cout << "   (Q)uit." << endl;
   cout << endl;
}
