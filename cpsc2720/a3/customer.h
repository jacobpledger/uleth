//**********************************************************************
/// \file
/// \brief Interface file for the Customer class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 1
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;

#include "exceptions.h"

/// A simple abstract base class to represent a Customer
class Customer
{
   public:
      /// Virtual destructor
      //
      /// This function does nothing. It is provided so that sub class
      /// objects are correctly destroyed
      virtual ~Customer() {}

      /// return a copy of yourself
      //
      /// \return a pointer to a copy of the current customer
      virtual Customer* clone() const = 0;
      
      /// Reads the information for a Customer from a stream
      //
      /// \param [in,out] is the stream to read from and the updated stream
      /// \return the updated stream, so that it can be cascaded
      virtual istream& read(istream& is) throw(input_format_error) = 0;

      /// Writes the information for a Customer to a stream
      //
      /// \param [in,out] os the stream to write to and the updated stream
      /// \return the updated stream, so that it can be cascaded
      virtual ostream& write(ostream& os) const throw() = 0;
};

/// overload the extraction operator
istream& operator>>(istream& is, Customer& c) throw(input_format_error);

/// overload the insertion operator
ostream& operator<<(ostream& os, const Customer& c) throw();
   
#endif
  
