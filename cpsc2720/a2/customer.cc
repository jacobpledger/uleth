//**********************************************************************
/// \file
/// \brief Implementation file for the customer class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;

#include "customer.h"

// overload the extraction operator
//
// this is a non-member function
/// \param [in,out] is the stream to read from and the updated stream
/// \param [out] c the customer to be extracted from the stream
/// \return the updated stream, so that it can be cascaded
/// \pre the stream is ready to be read from
/// \post \a c contains the customer read
istream& operator>>(istream& is, Customer& c) { return c.read(is); }

// overload the insertion operator
//
// this is a non-member function
/// \param [in,out] os the stream to read from and the updated stream
/// \param [in] c the customer to be inserted into the stream
/// \return the updated stream, so that it can be cascaded
/// \pre the stream is ready to be written to 
ostream& operator<<(ostream& os, const Customer& c) { return c.write(os); }
