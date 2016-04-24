//**********************************************************************
/// \file
/// \brief Implementation file for the customer class 
///
/// Sample solution for CS2720 Fall 2009 Assignment 1 Question 1
/// \author Rex Forsyth
/// \date Sept 24, 2009
///
/// Modified October 30, 2009 to add exceptions as required by assignment 2
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;

#include "customer.h"
#include "exceptions.h"

// overload the extraction operator
//
// this is a non-member function
/// \param [in,out] is the stream to read from and the updated stream
/// \param [out] c the customer to be extracted from the stream
/// \return the updated stream, so that it can be cascaded
/// \throw input_format_error if the the customer information is not the
///    correct format
/// \pre the stream is ready to be read from
/// \post \a c contains the customer read
istream& operator>>(istream& is, Customer& c) throw( input_format_error) {
   return c.read(is);
}

// overload the insertion operator
//
// this is a non-member function
/// \param [in,out] os the stream to read from and the updated stream
/// \param [in] c the customer to be inserted into the stream
/// \return the updated stream, so that it can be cascaded
/// \pre the stream is ready to be written to 
ostream& operator<<(ostream& os, const Customer& c) throw () {
   return c.write(os);
}
