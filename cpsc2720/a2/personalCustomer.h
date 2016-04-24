//**********************************************************************
///\file
/// \brief Interface file for the PersonalCustomer class
///
/// \author Jacob Pledger   (using Rex's solution)
/// \date Nov 6, 2009
//**********************************************************************
#ifndef PERSONAL_CUSTOMER_H
#define PERSONAL_CUSTOMER_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;

#include "customer.h"

/// A simple class to represent a PersonalCustomer who IS A Customer
class PersonalCustomer : public virtual Customer
{
   public:
      /// Create a personal customer with a name, and SIN
      //
      /// \param [in] name this personal customer's name; default \b UNKNOWN
      /// \param [in] sin this personal customer's SIN; defaults to 000000000
      PersonalCustomer(const string& name = "UNKNOWN",
	      const string& sin = "000000000")
	 : pName(name), SIN(sin) { }

      /// return a copy of yourself
      virtual Customer* clone() const;
      
      /// Reads the information for a personal customer from a stream
      virtual istream& read(istream& is)throw(input_format_error);
      
      /// Writes the information for a personal customer to a stream
      virtual ostream& write(ostream& os) const;

   private:
      string pName;   ///< the name of the personal customer
      string SIN;     ///< the SIN of the personal customer

};      
#endif
