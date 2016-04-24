/// \file
///
/// \author Jacob Pledger
/// \date Nov 30, 2009
///

#include "accountTest.h"

/// main program to execute the test suite
int main()
{
   CppUnit::TextTestRunner r;
   r.addTest(accountTest::suite());
   r.run();
   
   return 0;
}
