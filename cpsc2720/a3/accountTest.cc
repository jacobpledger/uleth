/// \file
///
/// \author Jacob Pledger
/// \date Nov 30, 2009
///

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>
#include <string>

#include "accountTest.h"

using std::istringstream;
namespace isstream = istringstream;

///set up test suite and test default constructors
void accountTest::setUp()
{
   act1 = new chequingSavingsAccount;
   act2 = new savingsAccount;
   act3 = new savingsAccount;
   act4 = new chequingAccount;;
   act5(act4);
}

///delete memory for all test accounts
void accountTest::tearDown()
{
   act1.cleanUp();
   act2.cleanUp();
   act3.cleanUp();
   act4.cleanUp();
   act5.cleanUp();
}

///tests the fill function, which also tests the derived constructors
void accountTest::testConstructors()
{
   CPPUNIT_ASSERT*act1.getAccountNumber() == "00000");
   CPPUNIT_ASSERT(act2.getAccountNumber() == "00000");
   CPPUNIT_ASSERT(act3.getAccountNumber() == "00000");
   CPPUNIT_ASSERT(act4.getAccountNumber() == "00000");
   CPPUNIT_ASSERT(act5.getAccountNumber() == act4.getAccountNumber());
}

///tests the read function on good input 
void accountTest::testGoodRead()
{
   string p = "P 1234567 5";
   isstream isp >> p;
   act2.read(isp);
   CPPUNIT_ASSERT_NO_THROW(act2.read());
   CPPUNIT_ASSERT(act2.getAccountNumber() == 1234567);
   
   string b = "B 7654321 99";
   isstream is1 >> b; //test business customer constructor
   act3.read(isb);
   CPPUNIT_ASSERT_NO_THROW(act3.read());
   CPPUNIT_ASSERT(act3.getAccountNumber() == 7654321);
}

///tests the exceptions for the read function
void accountTest::testBadRead()
{
   string x = "X 1234567 5";
   isstream isx >> x;
   act1.read(isx);
   CPPUNIT_ASSERT_THROW(act1.read(),input_format_error);
   
   string p = "P 123X567 10";
   isstream isp >> p;
   act2.read(isp);
   CPPUNIT_ASSERT_THROW(act2.read(),input_format_error);
   
   string p0 = "P 1234567 FaiL";
   isstream isp0 >> p0;
   act2.read(isp0);
   CPPUNIT_ASSERT_THROW(act2.read(),input_format_error);
   
   string b = "B 7654321 110";
   isstream isb >> b;
   act3.read(isb);
   CPPUNIT_ASSERT_THROW(act3.read(),input_format_error);
   
   string b0 = "B 7654321 fAIl";
   isstream isb0 >> b0;
   act3.read(isb0);
   CPPUNIT_ASSERT_THROW(act3.read(),input_format_error);
}

///tests deposit and withdraw functions
///it should be noted that this does NOT test for invalid
///input such as characters since there is no functionality
///to handle that situation within the program
void accountTest::testDepositWithdraw()
{
   // test deposit
   act1.deposit(10);
   act1.withdraw(10);
   CPPUNIT_ASSERT_NO_THROW(act1.withdraw());
   
   act2.deposit(7);
   act2.withdraw(7);
   CPPUNIT_ASSERT_NO_THROW(act2.withdraw());
   
   act3.deposit(325);
   act3.withdraw(325);
   CPPUNIT_ASSERT_NO_THROW(act3.withdraw());
   
   act4.deposit(3);
   act4.withdraw(1);
   CPPUNIT_ASSERT_NO_THROW(act4.withdraw());
   
   //test copy constructor
   act5(act4);
   act5.withdraw(2);
   CPPUNIT_ASSERT_NO_THROW(act5.withdraw());
}

//tests the exceptions thrown in withdraw
///this also does NOT check for invalid input
///such as characters for the same reason as
///testDepositWithdraw()
void accountTest::testBadWithdraw()
{
   act1.withdraw(70);
   CPPUNIT_ASSERT_THROW(act1.widthdraw(),insufficient_funds);
   act2.withdraw(1);
   CPPUNIT_ASSERT_THROW(act2.withdraw(),insufficient_funds);
   act3.withdraw(444);
   CPPUNIT_ASSERT_THROW(act3.withdraw(),insufficient_funds);
   act4.withdraw(1000000);
   CPPUNIT_ASSERT_THROW(act4.withdraw(),insufficient_funds);
   act5.withdraw(9999);
   CPPUNIT_ASSERT_THROW(*act5.withdraw(),insufficient_funds);
}

///test the <<, >>, and = operators
void accountTest::testOperators()
{
   //test >> operator
   string p = "P 1234567 5";
   isstream isp >> p;
   act2 >> isp;
   CPPUNIT_ASSERT_NO_THROW(act2.operator>>());
   CPPUNIT_ASSERT(act2.getAccountNumber() == 1234567);

   //test << operator
   ostream osp;
   act2 << osp;
   CPPUNIT_ASSERT_NO_THROW(act2.operator<<());

   //test >> operator
   string b = "B 7654321 99";
   isstream is1 >> b; 
   act3 >> isb;
   CPPUNIT_ASSERT_NO_THROW(act3.operator>>());
   CPPUNIT_ASSERT(act3.getAccountNumber() == 7654321);

   //test << operator
   ostream osb;
   act3 << osb;
   CPPUNIT_ASSERT_NO_THROW(act2.operator<<());

   //test assignment operator
   act1 = act2;
   CPPUNIT_ASSERT(act1 == act2);  
   act4 = act3;
   CPPUNIT_ASSERT(act3 == act4);
}
