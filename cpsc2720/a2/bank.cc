//**********************************************************************
/// \file
/// \brief Client test program to test the account class hierarchy.
///
/// It reads various types of accounts into a list from a file and allows
/// you to print the entire list of accounts, deposit money to an account,
/// withdraw money from an account and perform end of month updates.
/// All these operations are done polymorphically.
///
/// \author Jacob Pledger   (using Rex's solution)
/// \date Nov 6, 2009
//**********************************************************************
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

/// fill the list of accounts by reading data from a file
void fill(vector<Account*>&);

/// withdraw money from an account
void withdraw(const vector<Account*>&)throw(account_not_found);

/// deposit money to an account
void deposit(const vector<Account*>&)throw(account_not_found);

/// perform end of month updates on all accounts
void update(const vector<Account*>&);

/// Polymorphically print each account in the list
void print(const vector<Account*>& list);

/// Remove all items from the list
void clear(vector<Account*>& list);

/// find the index of the account which has this account number
int find(const vector<Account*>& accts, const string& number);

/// print a list of available options.
void printMenu();

///select from the list provided by printMenu()
void menuSelect(vector<Account*>& accts)throw(invalid_menu_choice);

/// the main function for the testing program
int main()
{
   vector<Account*> accounts;
   fill(accounts);
   printMenu();
   menuSelect(accounts);
   clear(accounts);
   
   return 0;
}

//initiate transaction
//
/// \param [in] loaded vector of accounts
/// \pre the vector has been loaded with accounts
/// \exception thrown if the user enters an invalid choice
void menuSelect(vector<Account*>& accts)throw(invalid_menu_choice)
{
   char toDo;
   try{
      do{
	 cout << "What do you want to do?" << endl;
	 cin >> toDo;
	 clrStream();    // get rid of any garbage including the new line
	 switch (toupper(toDo)) {
	    case 'L': print(accts); break;
	    case 'W': withdraw(accts); break;
	    case 'D': deposit(accts); break;
	    case 'U': update(accts); break;
	    case 'Q': break ;
	    default: throw invalid_menu_choice("Try Again.");
	 }
      } while (toupper(toDo) != 'Q');
   }
   catch(invalid_menu_choice)
   {
      cout << "Try Again." << endl;
      printMenu();
      menuSelect(accts);
   };
};

// fill the list of accounts by reading data from a file
//
/// \param [out] accounts exports the list of accounts
///
/// \pre the list is empty
//
// I have chosen to overwrite any accounts that are already in the list.
// If you want to append instead of overwrite, then comment out the "clear"
// function call.
void fill(vector<Account*>& accounts)
{
   string filename;
   ifstream acctFile;
   cout << "Enter the name of the file which holds the account data -- ";
   getline(cin,filename);
   openIn(acctFile, filename); //exception may be thrown here

   string code;
   clear(accounts);  // comment this line to append rather than overwrite
   int numAccounts = accounts.size();
   while (acctFile >> code) {
      if (code == "C") accounts.push_back(new ChequingAccount);
      else if (code == "S") accounts.push_back(new SavingsAccount);
      else if (code == "CS") accounts.push_back(new ChequingSavingsAccount);
      acctFile >> *accounts[numAccounts++];
   }
}

// Polymorphically print each account in the list
//
/// \param [in] accounts imports the list of accounts to print
void print(const vector<Account*>& accounts) {
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
void clear(vector<Account*>& list) {
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
/// \exception thrown if find() fails to loacte a valid account

void withdraw(const vector<Account*>& accounts)throw(account_not_found)
{
   string number;
   cout << "Enter the account number: ";
   cin >> number;

   int amount;
   cout << "Enter the amount to withdraw: ";
   cin >> amount;

   try{
      int foundAccount = find(accounts,number);
	 
      if (foundAccount == -1)
	 throw account_not_found("invalid account number");
      else
	 accounts[foundAccount]->withdraw(amount);
   }
   catch(account_not_found)
   {
      char check;
      cout << "Press q to quit or any other key to continue: " << endl;
      cin >> check;
      if(toupper(check) == 'Q')
	 exit(1);
      else
	 withdraw(accounts);
   }
}

// Deposit money to an account
//
/// \param [in] accounts imports the list of accounts 
/// \post the balance will be increased
/// \exception thrown if find() fails to locate an account

void deposit(const vector<Account*>& accounts)throw(account_not_found)
{
   string number;
   cout << "Enter the account number -- ";
   cin >> number;

   int amount;
   cout << "Enter the amount to deposit -- ";
   cin >> amount;

   try{
      int foundAccount = find(accounts, number);
      if (foundAccount == -1)
	 throw account_not_found("Invalid account number.");
      else
	 accounts[foundAccount]->deposit(amount);
   }
   catch(account_not_found)
   {
      char check;
      cout << "Press Q to quit or any other key to continue: " << endl;
      cin >> check;
      if (toupper(check) == 'Q')
	 exit(1);
      else
	 deposit(accounts);
   }
}

// Perform end of month updates on all accounts
//
/// \param [in] accounts imports the list of accounts 
void update(const vector<Account*>& accounts) {
   int numAccounts = accounts.size();
   for (int i = 0; i < numAccounts; i++)
      accounts[i]->updateMonthEnd();
}

// find the index of the account which has this account number
//
/// \param  [in] accounts imports the list of accounts
/// \param [in] number imports the account number to search for
/// \return the index of the account number, -1 if not found

int find(const vector<Account*>& accounts, const string& number) {
   int numAccounts = accounts.size();
   for (int i=0; i < numAccounts; i++) {
      if (accounts[i]->getAccountNumber() == number) return i;
   }
   return -1;   // not found
}

// print a list of available options
void printMenu() {
   cout << "Choose one of the following options:" << endl;
   cout << "   (L)ist the accounts and all their data." << endl;
   cout << "   (D)eposit to an account. " << endl;
   cout << "   (W)ithdraw from an account." << endl;
   cout << "   (U)pdate all accounts for end of month. " << endl;
   cout << "   (Q)uit." << endl;
   cout << endl;
}
