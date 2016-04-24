//**********************************************************************
///\file
/// \brief Interface file for the BusinessCustomer class
///
/// \author Jacob Pledger    (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#ifndef BUSINESS_CUSTOMER_H
#define BUSINESS_CUSTOMER_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;

#include "customer.h"

/// A simple class to represent a BusinessCustomer who IS A Customer
class BusinessCustomer : public virtual Customer
{
   public:
      /// Create a business customer with a name, and registration number
      //
      /// \param [in] name this business customer's name;
      ///             defaults to \b UNKNOWN
      /// \param [in] reg this business customer's registration number;
      ///             defaults to 000000000
      BusinessCustomer(const string& name = "UNKNOWN",
		       const string& reg = "000000000")
	 : bName(name), regNum(reg) { }

      /// return a copy of yourself
      virtual Customer* clone() const;
      
      /// Reads the information for a business customer from a stream
      virtual istream& read(istream& is)throw(input_format_error);
      
      /// Writes the information for a business customer to a stream
      virtual ostream& write(ostream& os) const;

   private:
      string bName;   ///< the name of the business customer
      string regNum;  ///< the registration number of the business customer

};      
#endif
