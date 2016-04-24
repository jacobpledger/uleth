#ifndef KMAPPERTEST_H
#define KMAPPERTEST_H

#include <iostream>
#include <fstream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestSuite.h>

#include <QtGui>

#include "../src/DataBackend.h"

//class PlaAdapter;

class KMapperTest :  public CppUnit::TestFixture {
   //Start
   CPPUNIT_TEST_SUITE(KMapperTest);

   //Test import/exporting files
   CPPUNIT_TEST(importAFile);
   CPPUNIT_TEST(importAFileWithDashes);
   CPPUNIT_TEST(exportAFile);
   //Test base conversions
   CPPUNIT_TEST(binaryToDecimal);
   CPPUNIT_TEST(decimalToBinary);
   CPPUNIT_TEST(decimalToBinaryList);
   CPPUNIT_TEST(truthTableValueToString);
   //Test setting variables
   CPPUNIT_TEST(settingNumberOfVariables);
   //CPPUNIT_TEST(settingVariableNames);
   //Test setting minterms
   CPPUNIT_TEST(settingMinTermsInt);
   CPPUNIT_TEST(settingMinTermsQString);
   CPPUNIT_TEST(settingMinTermsRowCol);
   //Test getting sizes
   CPPUNIT_TEST(gettingKMapSize);
   CPPUNIT_TEST(gettingTruthTableSize);
   //Test getting KMap headers
   CPPUNIT_TEST(gettingVerticalHeader);
   CPPUNIT_TEST(gettingHorizontalHeader);
   //Test incrementing minterms
   CPPUNIT_TEST(incrementMinTermTT);
   CPPUNIT_TEST(incrementMinTermKMap);
   //Test incrementing minterms
   CPPUNIT_TEST(minimizeBackend);
   //End
   CPPUNIT_TEST_SUITE_END();

  public:
   void setUp(void);
   void tearDown(void);

   //Test constructor
   ///DataBackend(int);
   
   //Test importing/exporting files
   void importAFile();
   void importAFileWithDashes();
   void exportAFile();

   //Test base conversions
   void binaryToDecimal();
   void decimalToBinary();
   void decimalToBinaryList();
   void truthTableValueToString();

   //Test incrementing minterms in TruthTables and KMaps
   void incrementMinTermTT();
   void incrementMinTermKMap();

   //Test setting number/names of variables
   //Also tests the getNumVars() function
   void settingNumberOfVariables();
   //Also tests the getVarNames() function (not yet implemented)
   //void settingVariableNames();
   
   //Test set/getting minterms
   //Tests setting minTerms with integers
   void settingMinTermsInt();
   //Tests setting minTerms with QStrings
   void settingMinTermsQString();
   //Tests setting minTerms in the KMap with a row and col integer value
   void settingMinTermsRowCol();

   //Tests getting the Size of a KMap
   //based on number of variables in the KMap
   void gettingKMapSize();
   //Tests getting the size of a Truth Table
   //based on number of variables in the KMap
   void gettingTruthTableSize();
   //Test getting KMap headers
   void gettingVerticalHeader();
   void gettingHorizontalHeader();

   //Test incrementing minterms
   void minimizeBackend();
  private:
   //Not sure if these are needed yet...
   std::ifstream inputFile_1; ///< An input file stream
   std::ifstream inputFile_2; ///< An input file stream

   void printTable(DataBackend dataBackendToPrint); ///< A helper function
   
};

#endif
