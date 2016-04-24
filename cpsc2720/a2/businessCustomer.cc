//**********************************************************************
///\file
/// \brief Implementation file for the BusinessCustomer class
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

#include "businessCustomer.h"

// return a copy of yourself
//
/// \return a pointer to a copy of a BusinessCustomer
Customer* BusinessCustomer::clone() const {return new BusinessCustomer; }

// Reads the information for a business customer from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \exception thrown if the account number is incorrectly written
/// \return the updated stream, so that it can be cascaded
istream& BusinessCustomer::read(istream& is)throw(input_format_error)
{
   string regNumCheck;
   is >> regNumCheck;  //read into a temp variable
   int checkLen = regNumCheck.length();
   char check = regNumCheck.at(checkLen);  //get the last character

   //check if the last character is an alphabetical character
   if (!isalpha(check) )
      throw input_format_error("incorrect account number format");
   else
   {
      regNum = regNumCheck;
      getline(is,bName);
   }
   return is;
}

// Writes the information for a business customer to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& BusinessCustomer::write(ostream& os) const {
   return os << 'B' << ' ' << regNum << ' ' << bName << endl;
}
