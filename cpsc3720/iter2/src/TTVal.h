/****************************************************************************
This file is part of KMapper.

KMapper is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
KMapper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KMapper.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

/*******************************************************************//**
\file
\brief Interface file for the TTVal class

\date Jan 31, 2010
\author Brian, Johnny, Nathan, Curtis B
**********************************************************************/

#include <QString>
#include <QTextStream>
#include <fstream>
#include <iostream>

class QTextStream;
class QDataStream;
class QString;


/*******************************************************************//**
\brief Class for accessing global values for truth table

This class is esentially a wrapper that is used to represent the values
ONE, ZERO, DONT_CARE and DASH used in the truth table. The class also
provides other functionality and overloaded operators.
**********************************************************************/
class TTVal
{
  public:
   /// Enumerated type
   enum TYPE {ZERO=256, ONE=257, DONT_CARE=258, DASH=259};

   /// Defaults val to ZERO
   TTVal();

   /// Sets the value to that of the val in the paramater ttVal.
   TTVal(const TTVal &t);

   
   /*****************************************************************/
   /*                       OVERLOADED OPERATORS                    */
   /*****************************************************************/
   
   /// Operator != Overloading.
   bool operator!=(TTVal t);

   /// Operator != Overloading.
   bool operator!=(TYPE t);

   /// Operator == Overloading.
   bool operator==(TTVal t);

   /// Operator == Overloading.
   bool operator==(TYPE t);

   /// Operator = Overloading for TTVal.
   void operator=(TTVal t);

   /// Operator = Overloading for TYPE
   void operator=(TYPE t);

   /// Operator ++ Overloading for convience.
   TTVal& operator++();

   /// Operator ++ Overloading for convience.
   TTVal& operator++(int notUsed);

   /// Operator += Overloading for convience.
   QString operator+=(TTVal t);


   /*****************************************************************/
   /*                         NORMAL FUNCTIONS                      */
   /*****************************************************************/

   /// Funtion to use when doing a switch on TTVal
   int sw();
   
   /// Increment val in loop order of ZERO->ONE->DONT_CARE->ZERO->ETC
   void increment();

   /// Converts val to a QString and returns it.
   QString toString();


   /*****************************************************************/
   /*                    FRIEND OUTPUT OPERATORS                    */
   /*****************************************************************/
      
   friend std::ostream &operator<<(std::ostream &stream, TTVal t);
   friend QTextStream &operator<<(QTextStream &stream, TTVal t);

  private:
   TYPE val;
};
