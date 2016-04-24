//**************************************************************************
/// \file
/// \brief header file for a library of auxiliary IO functions
///
/// \author Rex Forsyth
//**************************************************************************

#ifndef MYIO_H
#define MYIO_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;

#include "exceptions.h"

/// \brief Remove all data from the cin stream up to
/// and including the next new line character.
void clrStream();
char getResponse(char defalt);  ///< Get a character from the cin stream.
                                // If the character is a new line, return the
                                // defalt otherwise return the character
                                // entered. The cin stream is cleared
void getValid(int&);            ///< obtain a valid integer from the user
void getValid(double&);         ///< obtain a valid real number from the user
void openIn(ifstream& iStr, const string&) throw(invalid_file); 
                                ///< Attach a file to a stream.
                                // If unable to attach the given file, it
                                // will throw an exception
void openOut(ofstream& oStr, string& filename);  ///< Attach a file to a stream.
                                // If unable to attach the given file, it
                                // will continue asking for a file until
                                // a valid file is found and attached to oStr.
                                // filename will contain the name of the
                                // file attached. The cin stream is cleared.
#endif

