//**********************************************************************
///\file
/// \brief Interface file for the BusinessCustomer class
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 3
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#ifndef BUSINESS_CUSTOMER_H
#define BUSINESS_CUSTOMER_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;

#include "customer.h"
#include "exceptions.h"

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
		       const string& reg = "000000000") throw()
	 : bName(name), regNum(reg) { }

      /// return a copy of yourself
      virtual Customer* clone() const;
      
      /// Reads the information for a business customer from a stream
      virtual istream& read(istream& is) throw(input_format_error);
      
      /// Writes the information for a business customer to a stream
      virtual ostream& write(ostream& os) const throw();

   private:
      string bName;   ///< the name of the business customer
      string regNum;  ///< the registration number of the business customer

};      
#endif
