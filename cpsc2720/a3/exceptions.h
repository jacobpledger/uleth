//**********************************************************************
///\file 
///\brief the exception classes for the bank application
///
/// \author Rex Forsyth
/// \date Oct 30, 2009
///
/// Sample solution for CS2720 Fall 2009 Assignment 2
///
//**********************************************************************
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
using std::string;
using std::runtime_error;

/// An exception thrown when a file can not be opened
class invalid_file : public runtime_error {
   public:
      /// create the exception with the specified message
      //
      /// \param[in] what the message to be sent from the exception
      invalid_file(const string &what) : runtime_error(what) { }
};


/// An exception thrown when the user input does not have the correct format
class input_format_error : public runtime_error {
   public:
      /// create the exception with the specified message
      //
      /// \param[in] what the message to be sent from the exception
      input_format_error(const string &what) : runtime_error(what) { }
};

/// An exception thrown when the user attempts to withdraw more money
/// than is available
class insufficient_funds : public runtime_error {
   public:
      /// create the exception with the specified message
      //
      /// \param[in] what the message to be sent from the exception
      insufficient_funds(const string &what) : runtime_error(what) { }

};

/// An exception thrown when the user enters an invalid menu choice.
class invalid_menu_choice : public runtime_error {
   public:
      /// create the exception with the specified message
      //
      /// \param[in] what the message to be sent from the exception
      invalid_menu_choice(const string &what) : runtime_error(what) { }

};

/// An exception thrown when the user enters an invalid account number 
class account_not_found : public runtime_error {
   public:
      /// create the exception with the specified message
      //
      /// \param[in] what the message to be sent from the exception
      account_not_found(const string &what) : runtime_error(what) { }
};

#endif
