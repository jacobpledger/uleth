//**************************************************************************
/// \file
/// \brief implementation  file for a library of auxiliary IO functions 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**************************************************************************
#include <iostream>
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

#include "myio.h"

//**************************************************************************
// function to clear the cin stream up to and including the next new line
//
/// \post all data up to and including the next new line char
///                   is removed from cin
//**************************************************************************
void clrStream() {
   while (cin.peek() != '\n') cin.ignore();
   cin.ignore();
}

//**************************************************************************
// function to get a character response from the user and use the default
// response if the user just hits the return key
//
/// \param [in] defalt imports the default character to use if the enter
///                    key is pressed
/// \return \a defalt if the next character in the cin stream is a new line,
///                  otherwise returns the character entered
/// \post the cin stream is cleared
//**************************************************************************
char getResponse(char defalt) {
   char ch = cin.get();
   if (ch == '\n')
      ch = defalt;    // use the default character
   else
      clrStream();    // clear the newline and any garbage entered

   return ch;
}

//**************************************************************************
// function to obtain a valid integer from the user
//
/// \param [out] i exports the integer obtained
/// \post \a i will be a valid integer
//**************************************************************************
void getValid(int& i) {
   while (true) {
      cin >> i;
      if (cin.good() || cin.eof()) break;  // valid extraction or eof; so exit
      cout << "Invalid integer entered!! Reenter -- ";
      cin.clear();   // clear the error flag
      clrStream();   // clear bad data and garbage from the stream
   }
}

//**************************************************************************
// function to obtain a valid real number from the user
/// \param [out] x exports the number obtained
/// \post \a x will be a valid real number
//**************************************************************************
void getValid(double& x) {
   while (true) {
      cin >> x;
      if (cin.good() || cin.eof()) break;  // valid extraction or eof; so exit
      cout << "Invalid number entered!! Reenter -- ";
      cin.clear();   // clear the error flag
      clrStream();   // clear bad data and garbage from the stream
   }
}

//**************************************************************************
// function to attach a file to an input stream
//
/// \param [out] iStr exports the stream that the file was attached to
/// \param [in,out] filename imports the name of the file to be opened and
///                  exports the name of the file that was opened
/// \exception thrown if the user enters an unusable filename, or the
///                  program cannot open the file
/// \post \a iStr is attached to a valid file, ready for extraction
//**************************************************************************
void openIn(ifstream& iStr, string& filename)throw(invalid_file)
{
   while (true)
   {
      try{
	 iStr.open(filename.c_str());
	 if (iStr) break;  // succesfully attached the file so outta here
      } 
      // unable to attach file, so clear error flag, complain and get new name
      catch(invalid_file)
      {
	 iStr.clear(); 
	 cout << "Unable to open file!!! " << filename
	      << ".  Re-enter filename --  ";
	 getline(cin, filename);                          
      }
   }
}

//**************************************************************************
// function to attach a file to an output stream
//
/// \param [out] oStr exports the stream that the file was attached to
/// \param [in,out] filename imports the name of the file to be opened and
///                  exports the name of the file that was opened
/// \exception thrown if the user enters an unusable filename, or the
///                  program cannot open the file 
/// \post \a oStr is attached to a valid file, ready for insertion
//**************************************************************************
void openOut(ofstream& oStr, string& filename)throw(invalid_file)
{
   while (true)
   {
      try
      {
	 oStr.open(filename.c_str());
	 if (oStr) break;  // succesfully attached the file so outta here
      }
      catch(invalid_file)
      {
	 // unable to open file, so clear error flag, complain and get new name
	 oStr.clear();       
	 cout << "Unable to open file!!! " << filename
	      << ".  Re-enter filename --  ";
	 getline(cin, filename);
      }
   }
}
