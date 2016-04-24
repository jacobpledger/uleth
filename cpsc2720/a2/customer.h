//**********************************************************************
/// \file
/// \brief Interface file for the Customer class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "errors.h"
using std::istream;
using std::ostream;

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
      virtual istream& read(istream& is) = 0;

      /// Writes the information for a Customer to a stream
      //
      /// \param [in,out] os the stream to write to and the updated stream
      /// \return the updated stream, so that it can be cascaded
      virtual ostream& write(ostream& os) const = 0;
};

/// overload the extraction operator
istream& operator>>(istream& is, Customer& c);

/// overload the insertion operator
ostream& operator<<(ostream& os, const Customer& c);
   
#endif
  
