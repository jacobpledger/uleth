//**********************************************************************
///\file
/// \brief Implementation file for the BusinessCustomer class
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 3
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "businessCustomer.h"
#include "exceptions.h"

// return a copy of yourself
//
/// \return a pointer to a copy of a BusinessCustomer
Customer* BusinessCustomer::clone() const {return new BusinessCustomer(*this); }

// Reads the information for a business customer from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
/// \throw input_format_error if the the customer information is not the
///    correct format
/// \post if input was invalid, the customer is not changed, otherwise
///       this customer will be the one read.
istream& BusinessCustomer::read(istream& is) throw(input_format_error) {
   string tempRegNum;
   string tempBName;

   if (!(is >> tempRegNum))
      throw input_format_error("No registration number found");

   getline(is,tempBName);
   if (!is) throw input_format_error("No name found");

   // we read a valid registration number and name so assign to this object
   regNum  = tempRegNum;
   bName = tempBName;

   return is;
}
      
// Writes the information for a business customer to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& BusinessCustomer::write(ostream& os) const throw() {
   return os << 'B' << ' ' << regNum << ' ' << bName << endl;
}
