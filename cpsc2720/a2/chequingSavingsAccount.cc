//**********************************************************************
/// \file
/// \brief Implementation file for the ChequingSavingsAccount class 
///
/// \author Jacob Pledger   (using Rex's Solution)
/// \date Nov 6, 2009
//**********************************************************************
#include <iostream>
using std::istream;
using std::ostream;

#include "account.h"
#include "savingsAccount.h"
#include "chequingAccount.h"
#include "chequingSavingsAccount.h"

// Reads all information for a chequing savings account, from a stream
//
/// \param [in,out] is the stream to read from and the updated stream
/// \exception thrown by account::read() if incorrect
/// \return the updated stream, so that it can be cascaded
istream& ChequingSavingsAccount::read(istream& is)throw(input_format_error)
{
   Account::read(is);
   SavingsAccount::readExtra(is);
   return ChequingAccount::readExtra(is);
}

// Writes all information for a chequing savings account, to a stream
//
/// \param [in,out] os the stream to write to and the updated stream
/// \return the updated stream, so that it can be cascaded
ostream& ChequingSavingsAccount::write(ostream& os) const {
   Account::write(os);
   SavingsAccount::writeExtra(os);
   return ChequingAccount::writeExtra(os);
}

// Performs updates to the account at the end of the month
//
/// \post Interest earned has been added to the balance
/// \post The number of withdrawals is reset to 0
void ChequingSavingsAccount::updateMonthEnd() {
   SavingsAccount::updateMonthEnd();
   ChequingAccount::updateMonthEnd();
}

