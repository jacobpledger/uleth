#ifndef ERRORS_H
#define ERRORS_H
#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;

//thrown when a file cannot be read or written to
class invalid_file : public runtime_error
{
  public:
   invalid_file(const string& s) :runtime_error(s){}
};

//thrown when the input cannot be properly interpreted by the program
class input_format_error : public runtime_error
{
  public:
   input_format_error(const string& s) :runtime_error(s){}
};

//thrown in withdraw() functions when the balance is less than what the caller wants to withdraw
class insufficient_funds : public runtime_error
{
  public:
   insufficient_funds(const string& s) : runtime_error(s){}
};

//thrown when the user enters an incorrect value in the menu selection
class invalid_menu_choice : public runtime_error
{
  public:
   invalid_menu_choice(const string& s) : runtime_error(s){}
};


class account_not_found : public runtime_error
{
  public:
   account_not_found(const string& s) : runtime_error(s){}
};

#endif
