#ifndef ACCOUNT_TEST_H
#define ACCOUNT_TEST_H

/// \file
///
/// \author Jacob Pledger
/// \date Nv 30, 2009
///

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "account.h"

///tests the account class using macros
class accountTest : public CppUnit::TestFixture
{
   ///macros for creating test suite
   CPPUNIT_TEST_SUITE(accountTest);
   CPPUNIT_TEST(testConstructors); ///<test the main constructors of account and classes derived from it
   CPPUNIT_TEST(testGoodRead); ///<tests that the read function is correct for correct input
   CPPUNIT_TEST(testBadRead); ///<tests that the exceptions in read are correct when incorrect input is given
   CPPUNIT_TEST(testWrite); ///<tests that nothing goes wrong with the write function
   CPPUNIT_TEST(testDepositWithdraw); ///<mainly tests deposit, but also tests withdraw since the two are needed to test one another
   CPPUNIT_TEST(testBadWithdraw); ///<tests that the withdraw function throws the correct exception when the account does not have enough money
   CPPUNIT_TEST(testOperators); ///<tests the <<, >> and = operators
   CPPUNIT_TEST_SUITE_END();
   
  public:
   void setUp();
   void tearDown();
   void testConstructors();
   void testGoodRead();
   void testBadRead();
   void testWrite();
   void testDepositWithdraw();
   void testBadWithdraw();
   void testOperators();
   
  private:
   Account* act1;
   Account* act2;
   Account* act3;
   Account* act4;
   Account* act5;
};

#endif
