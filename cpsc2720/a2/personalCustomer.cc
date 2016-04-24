//**********************************************************************
///\file
/// \brief Implementation file for the PersonalCustomer class
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************

#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "personalCustomer.h"

// return a copy of yourself
//
/// \return a pointer to a copy of a PersonalCustomer
Customer* PersonalCustomer::clone() const {return new PersonalCustomer; }

// Reads the information for a PersonalCustomer from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \exception thrown if the SIN is of incorrect length or if it
///            contains alphabetic characters
/// \return the updated stream, so that it can be cascaded
istream& PersonalCustomer::read(istream& is)throw(input_format_error)
{
   string sinTemp;
   is >> sinTemp;

   if (sinTemp.length() != 9)
      throw input_format_error("incorrect number of characters");
   for (unsigned int i = 0; i <= sinTemp.length(); i++)
      if(isalpha(sinTemp.at(i)))
	 throw input_format_error("cannot contain alphabetic characters!");
   else
   {
      SIN = sinTemp;
      getline(is,pName);
   }
   return is;
}
      
// Writes the information for a PersonalCustomer to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& PersonalCustomer::write(ostream& os) const {
   return os << 'P' << ' ' << SIN << ' ' << pName << endl;
}
