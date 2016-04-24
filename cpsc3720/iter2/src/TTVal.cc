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

/*******************************************************************
\file
\brief Wrapper class for enumerated type to be used in DataBackend

\date Feb 26, 2010
\author Curtis B
\******************************************************************/

#include "TTVal.h"


/**
   Defaults val to ZERO
*/
TTVal:: TTVal()
{
   val=ZERO;
}

/**
   Sets the value to that of the val in the paramater ttVal.

   \param t The TTVal, whos val value the internal variable
   will be set to.
*/
TTVal::TTVal(const TTVal &t)
{
   val=t.val;
}


/**
   Sets the value of val directly.

   Sets the val directly using scoped values.
   Example: TTVal s(TTVal::ZERO); creates a TTVal with val
   set to ZERO
   ****REMOVED FOR NOW****
*/
// TTVal(TYPE t){val=t;}



/*****************************************************************/
/*****************************************************************/
/*                       OVERLOADED OPERATORS                    */
/*****************************************************************/
/*****************************************************************/

/**
   Operator != Overloading.

   Overloads the  != operator for the wrapped enumerated type,
   returns true only if the two compared values are NOT equal.
   Example: TTVal s = ZERO, t = ONE;
   s!=t; returns true
   \param t The TTVal to be compared to this objects value.
*/
bool TTVal::operator!=(TTVal t)
{
   if(val!=t.val)
      return true;
   return false;
}


/**
   Operator != Overloading.

   Overloads the  != operator for the wrapped enumerated type,
   returns true only if the two compared values are NOT equal.
   Example: TTVal s = ZERO;
   s != TTVal::ONE; returns true;
   \param t The enumerated type to be compared to this objects value.
*/
bool TTVal::operator!=(TYPE t)
{
   if(val!=t)
      return true;
   return false;
}


/**
   Operator == Overloading.

   Overloads the  != operator for the wrapped enumerated type,
   returns true only if the two compared values ARE equal.
   Example: TTVal s = TTVal::ZERO, t = TTVal::ONE;
   "s==t" returns true
   \param t The TTVal to be compared to this objects value.
*/
bool TTVal::operator==(TTVal t)
{
   if(val==t.val)
      return true;
   return false;
}


/**
   Operator == Overloading.

   Overloads the  != operator for the wrapped enumerated type,
   returns true only if the two compared values ARE equal.
   Example: TTVal s = TTVal::ZERO, t = TTVal::ONE;
   "s==t" returns true
   \param t The enumerated type to be compared to this objects value.
*/
bool TTVal::operator==(TYPE t)
{
   if(val==t)
      return true;
   return false;
}


/**
   Operator = Overloading for TTVal.

   Sets the = operator for the class, directly sets the value of
   the parameter to that of the internal variable.
   Example: TTVal s = ZERO, t;
   t=s; will result in t.val being ZERO
   \param t The enumerated type to be compared to this objects value.
*/	 
void TTVal::operator=(TTVal t)
{
   val=t.val;
}


/**
   Operator = Overloading for the internal enum type
	 
   Sets the = operator for the enumerated type, used for internal
   functionality only.
   Example : this.val = ZERO; will result in val for this object
   to be set to ZERO.
   \param t Enumerated type that val will be set to.
*/
void TTVal::operator=(TYPE t)
{
   val=t;
}


/**
   Operator ++ Overloading for convience.
   
   Calls the function increment that moves the value to the next
   enumerated type value accordingly. PREPENDED.
   Example: TTVal s = ZERO;
   ++s; will result in s.val being changed to ONE.
*/
TTVal& TTVal::operator++()
{
   increment();
   return *this;
}


/**
   Operator ++ Overloading for convience.
   
   Calls the function increment that moves the value to the next
   enumerated type value accordingly. APPENDED.
   Example: TTVal s = ZERO;
   s++; will result in s.val being changed to ONE.
   \param notUsed Unused value
*/
TTVal& TTVal::operator++(int notUsed)
{
   notUsed=1;
   increment();
   return *this;
}


/**
   Operator += Overloading for convience.

   Appends the value of the parameters internal value to this
   objects value and returns it as a QString
   \param t The TTVal to be used with appending to this objects value.
*/
QString TTVal::operator+=(TTVal t)
{
   return (toString()+t.toString());
}


      
	
/*****************************************************************/
/*****************************************************************/
/*                         NORMAL FUNCTIONS                      */
/*****************************************************************/
/*****************************************************************/


/**
   Accessor to be used when switching on TTV.

   \post Returns the integer value of the enumerated type for
   use in switching
*/
int TTVal::sw()
{
   return val;
}
   

/**
   Increment val in loop order of ZERO->ONE->DONT_CARE->ZERO->ETC

   Allows single incrementation of the internal enumerated type
   that will loop back to zero if it is called while the internal
   value is DONT_CARE, else it will increment normally.
   Example: TTVal s = ZERO;
   s.increment(); will result in s.val being changed to ONE.
*/
void TTVal::increment()
{
   switch(val)
   {
      case ZERO:
	 val = ONE;
	 break;
      case ONE:
	 val = DONT_CARE;
	 break;
      case DONT_CARE:
	 val = ZERO;
	 break;
      case DASH:
      default:
	 //Leave the dash alone, shouldn't be used
	 break;
   }
}

      
/**
   Converts val to a QString and returns it.
*/
QString TTVal::toString()
{
   switch(val)
   {
      case ZERO:
	 return "0";
	 break;
      case ONE:
	 return "1";
	 break;
      case DONT_CARE:
	 return "X";
	 break;
      case DASH:
	 return "-";
	 break;
      default:
	 return "";
	 break;
	       
	 // Should not do anything
   }
}


/*****************************************************************/
/*                    FRIEND OUTPUT OPERATORS                    */
/*****************************************************************/


/**
   Output operator overloading for Standard Lib ostream.

   Overloads the operator for the standard library ostreams and
   returns the stream for use with cascading.
   \param stream The ostream to which output will be directed.
   \param t The TTVal that is going to be written to the ostream.
*/
std::ostream &operator<<(std::ostream &stream, TTVal t)
{
   switch(t.val)
   {
      case TTVal::ZERO:
      case TTVal::ONE:
	 stream << t.val-TTVal::ZERO;
	 break;
      case TTVal::DONT_CARE:
	 stream << "X";
	 break;
      case TTVal::DASH:
	 stream << "-";
	 break;
      default:
	 stream << "";
	 break;
   }
   return stream;
}



/**
   Output operator overloading for Standard Lib ostream.
   
   Overloads the operator for the QTextStream and
   returns the stream for use with cascading.
   \param stream The QTextStream to which output will be directed.
   \param t The TTVal that is going to be written to the QTextStream.
*/
QTextStream &operator<<(QTextStream &stream, TTVal t)
{
   switch(t.val)
   {
      case TTVal::ZERO:
      case TTVal::ONE:
	 stream << t.val-TTVal::ZERO;
	 break;
      case TTVal::DONT_CARE:
	 stream << "D";
	 break;
      case TTVal::DASH:
	 stream << "-";
	 break;
      default:
	 stream << "";
	 break;
   }
   return stream;
}
