//**********************************************************************
///\file
/// \brief Interface file for the PersonalCustomer class
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 2
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef PERSONAL_CUSTOMER_H
#define PERSONAL_CUSTOMER_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;

#include "customer.h"
#include "exceptions.h"

/// A simple class to represent a PersonalCustomer who IS A Customer
class PersonalCustomer : public virtual Customer
{
   public:
      /// Create a personal customer with a name, and SIN
      //
      /// \param [in] name this personal customer's name; default \b UNKNOWN
      /// \param [in] sin this personal customer's SIN; defaults to 000000000
      PersonalCustomer(const string& name = "UNKNOWN",
		       const string& sin = "000000000") throw()
	 : pName(name), SIN(sin) { }

      /// return a copy of yourself
      virtual Customer* clone() const;
      
      /// Reads the information for a personal customer from a stream
      virtual istream& read(istream& is) throw(input_format_error);
      
      /// Writes the information for a personal customer to a stream
      virtual ostream& write(ostream& os) const throw();

   private:
      string pName;   ///< the name of the personal customer
      string SIN;     ///< the SIN of the personal customer

};      
#endif
