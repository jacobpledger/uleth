#include <vector>
#include <fstream>
#include "customer.cc"
#include "account.cc"
#include "personalCustomer.cc"
#include "businessCustomer.cc"
#include "savings.cc"
#include "chequing.cc"
#include "cheqsav.cc"
using namespace std;

void loadAccounts(vector<account*> v);
void list(vector<account*>v);
void withdraw(vector<account*>v);
void deposit(vector<account*>v);
void update(vector<account*>v);

int main()
{
   vector<account*> v;
   loadAccounts(v);
   char sel;
   while(sel != 'q')
   {
      cout << "Choose an item (enter lowercase of indicated letter):" << endl
	   << "List(L)" << endl
	   << "Withdraw(W)" << endl
	   << "Deposit(D)" << endl
	   << "Update(U)" << endl
	   << "Quit(Q)" << endl;
      cin >> sel;
      if (sel == 'l')
	 list(v);

      else if (sel == 'w')
	 withdraw(v);
      
      else if (sel == 'd')
	 deposit(v);
      
      else if (sel == 'u')
	 update(v);
   }
   
   return 0;
};

void loadAccounts(vector<account*> v)
{
   string filename;
   ifstream infile;
   account* temp;
   cout << "Please enter the file containing the account information: "
	<< endl;
   cin >> filename;
   infile.open(filename.c_str());
   infile >> *temp;

   while (!infile.eof())
   {
      v.push_back(temp);
      infile >> *temp;
   }
};

///\pre all pointers are initialized
///\post all account information is output to the screen

void list(vector<account*>v)
{
    for (int i = 0; i < v.size(); i++)
       cout << v[i];
};

///\pre balance can be negative, no error checking
///\post the amount has been removed from the specified account, balance can be negative here also
//\param the amount entered after prompt will be removed from the balance, can be negative

void withdraw(vector<account*>v)
{
   string num;
   cout << "Please enter the account number: ";
   cin >> num;
   
   int amt;
   cout << "Please enter an amount: ";
	 cin >> amt;
	 for (int i = 0; i < v.size(); i++)
	 {
	    if (num == v[i]->getAccountNumber())
	       v[i]->withdraw(amt);
	 }  
}

///\pre balance can be negative
///\post the balance has been increased by the specified amount
///\param can be negative, will be added to balance

void deposit(vector<account*>v)
{
   string num;
   cout << "Please enter the account number: ";
   cin >> num;
   int dpst;
   cout << "Please enter an amount: ";
   cin >> dpst;

   for (int i = 0; i < v.size(); i++)
      if (num == v[i]->getAccountNumber())
	 v[i]->deposit(dpst);
   
};

///\post all accounts updated as per their individual conditions

void update(vector<account*>v)
{
   for (int i = 0; i < v.size(); i++)
      v[i]->updateMonthEnd();
};
	 
	 
