//**********************************************************************
///\file
/// \brief Implementation file for the PersonalCustomer class
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 2
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "personalCustomer.h"
#include "exceptions.h"

// return a copy of yourself
//
/// \return a pointer to a copy of a PersonalCustomer
Customer* PersonalCustomer::clone() const {return new PersonalCustomer(*this); }

// Reads the information for a PersonalCustomer from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \return the updated stream, so that it can be cascaded
/// \throw input_format_error if the the customer information is not the
///    correct format
/// \post if input was invalid, the customer is not changed, otherwise
///       this customer will be the one read.
istream& PersonalCustomer::read(istream& is) throw(input_format_error) {

   string tempSIN;
   string tempPName;

   if (!(is >> tempSIN)) throw input_format_error("No SIN found");

   getline(is,tempPName);
   if (!is)  throw input_format_error("No name found");

   // we read a valid SIN and name so assign to this object
   SIN = tempSIN;
   pName = tempPName;
   
   return is;
}
      
// Writes the information for a PersonalCustomer to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& PersonalCustomer::write(ostream& os) const throw() {
   return os << 'P' << ' ' << SIN << ' ' << pName << endl;
}

 
