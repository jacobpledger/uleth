#include <KMapperTest.h>
#include <iostream>
#include <math.h>
void KMapperTest::setUp(){
 
}

void KMapperTest::tearDown(){
 
};

//A helper function for when you want to print the truth table
void KMapperTest::printTable(DataBackend dataBackendToPrint){ 
   std::cout << std::endl;
   for(int i = 0; i < dataBackendToPrint.getTable().size(); i++){
      for(int j = 0; j < dataBackendToPrint.getTable()[i].size(); j++){
	 switch(dataBackendToPrint.getTable()[i][j]){
	    case TTVal::ZERO:
	       std::cout << "0";
	       break;
	    case TTVal::ONE:
	       std::cout << "1";
	       break;
	    case TTVal::DONT_CARE:
	       std::cout << "x";
	       break;
	    case TTVal::DASH:
	       std::cout << "x";
	       break;
	    default:
	       std::cout << "SOMETHING_UNPRINTABLE"; //Only testers will see this
	       break;
	 }
      }
      std::cout << std::endl;
   }
}

void KMapperTest::importAFile(){

   //Manually make TruthTable to test against
   DataBackend test(3);   
   test.setMinTerm(1, TTVal::ONE);
   test.setMinTerm(5,TTVal::ONE);

   //Read in PLA file. This creates a TT. Check that it opens correctly
   DataBackend plaImport(3);
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/testImport1.pla") == 1);
   //Compare two truthtables
   CPPUNIT_ASSERT(plaImport.getTable() == test.getTable());

}


void KMapperTest::importAFileWithDashes(){
   //TEST1 (All Minterms are 1s)
   //Create a TruthTable to test against
   DataBackend test1(3);
   test1.setMinTerm(0, TTVal::ONE);
   test1.setMinTerm(1, TTVal::ONE);
   test1.setMinTerm(2, TTVal::ONE);
   test1.setMinTerm(3, TTVal::ONE);
   test1.setMinTerm(4, TTVal::ONE);
   test1.setMinTerm(5, TTVal::ONE);
   test1.setMinTerm(6, TTVal::ONE);
   test1.setMinTerm(7, TTVal::ONE);

   //Read .PLA File. This action creates another TruthTable
   DataBackend plaImport1(3);
   CPPUNIT_ASSERT(plaImport1.importFile("testPlaFiles/testImport2.pla") == 1);

   //Check Number of Variables
   CPPUNIT_ASSERT(plaImport1.getNumVars()== 3);

   //Compare two Truth Tables
   CPPUNIT_ASSERT(plaImport1.getTable() == test1.getTable());
   
   

   //TEST2 (3 Variables , two dashes)
   //Create a TruthTable to test against
   DataBackend test2(3);
   test2.setMinTerm(0, TTVal::ZERO);
   test2.setMinTerm(1, TTVal::ZERO);
   test2.setMinTerm(2, TTVal::ZERO);
   test2.setMinTerm(3, TTVal::ZERO);
   test2.setMinTerm(4, TTVal::ONE);
   test2.setMinTerm(5, TTVal::ONE);
   test2.setMinTerm(6, TTVal::ONE);
   test2.setMinTerm(7, TTVal::ONE);

   //Read .PLA File. This action creates another TruthTable
   DataBackend plaImport2(3);
   CPPUNIT_ASSERT(plaImport2.importFile("testPlaFiles/testImport3.pla") == 1);

   //Check Number of Variables
   CPPUNIT_ASSERT(plaImport2.getNumVars()== 3);   

   //Compare two Truth Tables
   CPPUNIT_ASSERT(plaImport2.getTable() == test2.getTable());



   
   //TEST3 (3 Variables , one dash)
   //Create a TruthTable to test against
   DataBackend test3(3);
   test3.setMinTerm(0, TTVal::ZERO);
   test3.setMinTerm(1, TTVal::ZERO);
   test3.setMinTerm(2, TTVal::ZERO);
   test3.setMinTerm(3, TTVal::ONE);
   test3.setMinTerm(4, TTVal::ZERO);
   test3.setMinTerm(5, TTVal::ZERO);
   test3.setMinTerm(6, TTVal::ZERO);
   test3.setMinTerm(7, TTVal::ONE);

   //Read .PLA File. This action creates another TruthTable
   DataBackend plaImport3(3);
   CPPUNIT_ASSERT(plaImport3.importFile("testPlaFiles/testImport4.pla") == 1);

   //Check Number of Variables
   CPPUNIT_ASSERT(plaImport3.getNumVars()== 3);   

   //Compare two Truth Tables
   CPPUNIT_ASSERT(plaImport3.getTable() == test3.getTable());



   
   //TEST4 (OVERWRITES)
   //Create a TruthTable to test against
   DataBackend test4(3);
   test4.setMinTerm(0, TTVal::ZERO);
   test4.setMinTerm(1, TTVal::ZERO);
   test4.setMinTerm(2, TTVal::ZERO);
   test4.setMinTerm(3, TTVal::ZERO);
   test4.setMinTerm(4, TTVal::ZERO);
   test4.setMinTerm(5, TTVal::ZERO);
   test4.setMinTerm(6, TTVal::ZERO);
   test4.setMinTerm(7, TTVal::ONE);

   //Read .PLA File. This action creates another TruthTable
   DataBackend plaImport4(3);
   CPPUNIT_ASSERT(plaImport4.importFile("testPlaFiles/testImport5.pla") == 1);

   //Check Number of Variables
   CPPUNIT_ASSERT(plaImport4.getNumVars()== 3);   

   //Compare two Truth Tables
   CPPUNIT_ASSERT(plaImport4.getTable() == test4.getTable());

   
   

   //TEST5 (BAD INPUT)
   //Read .PLA File. Input strings contain other characters 
   DataBackend plaImport5(3);
   CPPUNIT_ASSERT(plaImport5.importFile("testPlaFiles/testbedImport5.pla") == 0);     


   
   
   //TEST6 (BAD FORMAT)
   //Read .PLA File. This file has wrong format
   DataBackend plaImport6(3);
   CPPUNIT_ASSERT(plaImport6.importFile("testPlaFiles/testbedImport6.pla") == 0);   
   
}




void KMapperTest::exportAFile(){
   //Make two truth tables for comparing
   DataBackend plaImport(6);
   DataBackend toExportTest(6);
   DataBackend toImportTest(6);
   //set terms for toExportTest to match /testPlaFiles/setMinTermsTest2.pla"
   toExportTest.setMinTerm(0, TTVal::ONE);
   toExportTest.setMinTerm(1, TTVal::ONE);
   toExportTest.setMinTerm(16, TTVal::ONE);
   toExportTest.setMinTerm(25, TTVal::ONE);
   toExportTest.setMinTerm(54, TTVal::ONE);
   toExportTest.setMinTerm(42, TTVal::ONE);
   //run minimize
   toExportTest.minimize(TTVal::ONE);
   //export toExportTest to a PLA file
   CPPUNIT_ASSERT(toExportTest.exportFile("testPlaFiles/exportFileTest1.pla"));
   //import that file back in, to toImportTest
   CPPUNIT_ASSERT(toImportTest.importFile("testPlaFiles/exportFileTest1.pla"));
   //set Pla import to the file that toImportTest should equal
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/exportFileTest2.pla") == 1);
   //check that the tables match
   CPPUNIT_ASSERT(plaImport.getTable() == toImportTest.getTable());
}

void KMapperTest::binaryToDecimal(){
   DataBackend tester1;
   CPPUNIT_ASSERT(tester1.binToDec("0") == 0);
   CPPUNIT_ASSERT(tester1.binToDec("1") == 1);
   CPPUNIT_ASSERT(tester1.binToDec("101") == 5);
   CPPUNIT_ASSERT(tester1.binToDec("110") == 6);	       
}

void KMapperTest::decimalToBinary(){
   DataBackend tester1;   
   CPPUNIT_ASSERT(tester1.decToBin(0) == "0");
   CPPUNIT_ASSERT(tester1.decToBin(1) == "1");
   CPPUNIT_ASSERT(tester1.decToBin(5) == "101");
   CPPUNIT_ASSERT(tester1.decToBin(6) == "110");
}

void KMapperTest::decimalToBinaryList(){
   DataBackend tester1(3);
   //testing to match pattern 101 = 5
   QList<bool> testBinList = tester1.decToBinList(2);
   CPPUNIT_ASSERT(testBinList.at(0) == true);
   CPPUNIT_ASSERT(testBinList.at(1) == false);
//   CPPUNIT_ASSERT(testBinList.at(2) == true);
   
}

void KMapperTest::truthTableValueToString(){
   DataBackend test;
   CPPUNIT_ASSERT(test.valueToString(TTVal::ZERO) == "0");
   CPPUNIT_ASSERT(test.valueToString(TTVal::ONE) == "1");
   CPPUNIT_ASSERT(test.valueToString(TTVal::DONT_CARE) == "X");
}

void KMapperTest::incrementMinTermTT(){
   //very basic test
   DataBackend test;
   //increment row 1 in Truth Table from TTVal::ZERO to TTVal::ONE
   test.increment(1);
   //see if it worked
   CPPUNIT_ASSERT(test.getMinTerm(1) == TTVal::ONE);
}

void KMapperTest::incrementMinTermKMap(){
   //very basic test
   DataBackend test;
   //increment row 1 column 0 in KMAP from TTVal::ZERO to TTVal::ONE
   test.increment(1, 0);
   //see if it worked
   CPPUNIT_ASSERT(test.getMinTerm(1, 0) == TTVal::ONE);
}


void KMapperTest::settingNumberOfVariables(){
   //testing all possible numbers of variables
   DataBackend tester1;
   tester1.setNumVars(2);
   CPPUNIT_ASSERT(tester1.getNumVars() == 2);
   tester1.setNumVars(3);
   CPPUNIT_ASSERT(tester1.getNumVars() == 3);
   tester1.setNumVars(4);
   CPPUNIT_ASSERT(tester1.getNumVars() == 4);
   tester1.setNumVars(5);
   CPPUNIT_ASSERT(tester1.getNumVars() == 5);
   tester1.setNumVars(6);
   CPPUNIT_ASSERT(tester1.getNumVars() == 6);
   
}

//requires getVarNames method
//void KMapperTest::settingVariableNames(){
//   DataBackend tester1;
   
void KMapperTest::settingMinTermsInt(){
   //test default
   DataBackend test;
   DataBackend plaImport;//default to two variables, 4 minterms
   //testing a default sized truth table
   test.setMinTerm(2, TTVal::ONE);
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest1.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getTable() == test.getTable());
  
   //testing a 6 variable truth table
   test.setNumVars(6);
   test.setMinTerm(2, TTVal::ZERO);//undoes the setting from the test above
   test.setMinTerm(1, TTVal::ONE);
   test.setMinTerm(16, TTVal::DONT_CARE);
   test.setMinTerm(12, TTVal::DONT_CARE);
   test.setMinTerm(25, TTVal::ONE);
   test.setMinTerm(54, TTVal::ONE);
   test.setMinTerm(63, TTVal::DONT_CARE);
   test.setMinTerm(42, TTVal::ONE);
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest2.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getTable() == test.getTable());
 
}

void KMapperTest::settingMinTermsQString(){
   DataBackend test;
   DataBackend plaImport;

   //testing against a 6 variable truth table
   //Also tests that TTVal::DONT_CAREs read in from pla
   //are converted to TTVal::ONEs.
   test.setNumVars(6);
   test.setMinTerm("000001", TTVal::ONE);
   test.setMinTerm("010000", TTVal::DONT_CARE);
   test.setMinTerm("001100", TTVal::DONT_CARE);
   test.setMinTerm("011001", TTVal::ONE);
   test.setMinTerm("110110", TTVal::ONE);
   test.setMinTerm("111111", TTVal::DONT_CARE);
   test.setMinTerm("101010", TTVal::ONE);   
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest2.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getTable() == test.getTable());

}

void KMapperTest::settingMinTermsRowCol(){
   //test default
   DataBackend test;
   DataBackend plaImport;//default to two variables, 4 minterms
   
   //testing a default sized truth table
   test.setMinTerm(0, 1, TTVal::ONE);
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest1.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getTable() == test.getTable());
}
   

void KMapperTest::gettingKMapSize(){
   DataBackend test;
   int nRowsTest = -1; //default to -1 which is never correct
   int nColsTest = -1; //default to -1 which is never correct
   //testing default size, 2 by 2
   test.getKMapSize(nRowsTest, nColsTest);
   CPPUNIT_ASSERT(nRowsTest == 2);
   CPPUNIT_ASSERT(nColsTest == 2);
   test.setNumVars(6);
   test.getKMapSize(nRowsTest, nColsTest);
   CPPUNIT_ASSERT(nRowsTest == 8);
   CPPUNIT_ASSERT(nColsTest == 8);
   
}

void KMapperTest::gettingTruthTableSize(){
   DataBackend test;
   int nRowsTest = -1; //default to -1 which is never correct
   int nColsTest = -1; //default to -1 which is never correct
   //testing default size, 2 columns and 4 rows
   test.getTruthTableSize(nRowsTest, nColsTest);
   CPPUNIT_ASSERT(nRowsTest == 4);
   CPPUNIT_ASSERT(nColsTest == 3);
   test.setNumVars(6);
   test.getTruthTableSize(nRowsTest, nColsTest);
   CPPUNIT_ASSERT(nRowsTest == 64);
   CPPUNIT_ASSERT(nColsTest == 7);
   
}

void KMapperTest::gettingVerticalHeader(){
   DataBackend plaImport;//default to two variables, 4 minterms
   
   //testing a default sized truth table with vars x,y
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest1.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getVerticalTitle() == "y");
   QList<QString> headerVarNames = plaImport.getVerticalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "0");
   CPPUNIT_ASSERT(headerVarNames[1] == "1");
   CPPUNIT_ASSERT(headerVarNames.size() == 2);

   DataBackend defaultTT2Vars(2); //defaultvariables A,B
   CPPUNIT_ASSERT(defaultTT2Vars.getVerticalTitle() == "B");
   headerVarNames = defaultTT2Vars.getVerticalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "0");
   CPPUNIT_ASSERT(headerVarNames[1] == "1");
   CPPUNIT_ASSERT(headerVarNames.size() == 2);
   
   DataBackend defaultTT3Vars(3); //defaultvariables A,B,C
   CPPUNIT_ASSERT(defaultTT3Vars.getVerticalTitle() == "C");
   headerVarNames = defaultTT3Vars.getVerticalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "0");
   CPPUNIT_ASSERT(headerVarNames[1] == "1");
   CPPUNIT_ASSERT(headerVarNames.size() == 2);

   DataBackend defaultTT4Vars(4); //defaultvariables A,B,C,D
   CPPUNIT_ASSERT(defaultTT4Vars.getVerticalTitle() == "C,D");
   headerVarNames = defaultTT4Vars.getVerticalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "00");
   CPPUNIT_ASSERT(headerVarNames[1] == "01");
   CPPUNIT_ASSERT(headerVarNames[2] == "11");
   CPPUNIT_ASSERT(headerVarNames[3] == "10");
   CPPUNIT_ASSERT(headerVarNames.size() == 4);

   DataBackend defaultTT5Vars(5); //defaultvariables A,B,C,D,E
   CPPUNIT_ASSERT(defaultTT5Vars.getVerticalTitle() == "D,E");
   headerVarNames = defaultTT5Vars.getVerticalKMapHeader();   
   CPPUNIT_ASSERT(headerVarNames[0] == "00");
   CPPUNIT_ASSERT(headerVarNames[1] == "01");
   CPPUNIT_ASSERT(headerVarNames[2] == "11");
   CPPUNIT_ASSERT(headerVarNames[3] == "10");
   CPPUNIT_ASSERT(headerVarNames.size() == 4);
   
   DataBackend defaultTT6Vars(6); //defaultvariables A,B,C,D,E,F
   CPPUNIT_ASSERT(defaultTT6Vars.getVerticalTitle() == "D,E,F");
   headerVarNames = defaultTT6Vars.getVerticalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "000");
   CPPUNIT_ASSERT(headerVarNames[1] == "001");
   CPPUNIT_ASSERT(headerVarNames[2] == "011");
   CPPUNIT_ASSERT(headerVarNames[3] == "010");
   CPPUNIT_ASSERT(headerVarNames[4] == "110");
   CPPUNIT_ASSERT(headerVarNames[5] == "111");
   CPPUNIT_ASSERT(headerVarNames[6] == "101");
   CPPUNIT_ASSERT(headerVarNames[7] == "100");
   CPPUNIT_ASSERT(headerVarNames.size() == 8);

}

void KMapperTest::gettingHorizontalHeader(){
   DataBackend plaImport;//default to two variables, 4 minterms
   
   //testing a default sized truth table with vars x,y
   CPPUNIT_ASSERT(plaImport.importFile("testPlaFiles/setMinTermsTest1.pla") == 1);
   CPPUNIT_ASSERT(plaImport.getHorizontalTitle() == "x");
   QList<QString> headerVarNames = plaImport.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "0");

   CPPUNIT_ASSERT(headerVarNames[1] == "1");
   CPPUNIT_ASSERT(headerVarNames.size() == 2);
   
   DataBackend defaultTT2vars(2); //defaultvariables A,B
   CPPUNIT_ASSERT(defaultTT2vars.getHorizontalTitle() == "A");
   headerVarNames = defaultTT2vars.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "0");
   CPPUNIT_ASSERT(headerVarNames[1] == "1");
   CPPUNIT_ASSERT(headerVarNames.size() == 2);

   
   DataBackend defaultTT3vars(3); //defaultvariables A,B,C
   CPPUNIT_ASSERT(defaultTT3vars.getHorizontalTitle() == "A,B");
   headerVarNames = defaultTT3vars.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "00");
   CPPUNIT_ASSERT(headerVarNames[1] == "01");
   CPPUNIT_ASSERT(headerVarNames[2] == "11");
   CPPUNIT_ASSERT(headerVarNames[3] == "10");
   CPPUNIT_ASSERT(headerVarNames.size() == 4);

   DataBackend defaultTT4vars(4); //defaultvariables A,B,C,D
   CPPUNIT_ASSERT(defaultTT4vars.getHorizontalTitle() == "A,B");
   headerVarNames = defaultTT4vars.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "00");
   CPPUNIT_ASSERT(headerVarNames[1] == "01");
   CPPUNIT_ASSERT(headerVarNames[2] == "11");
   CPPUNIT_ASSERT(headerVarNames[3] == "10");
   CPPUNIT_ASSERT(headerVarNames.size() == 4);

   DataBackend defaultTT5vars(5); //defaultvariables A,B,C,D,E
   CPPUNIT_ASSERT(defaultTT5vars.getHorizontalTitle() == "A,B,C");
   headerVarNames = defaultTT5vars.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "000");
   CPPUNIT_ASSERT(headerVarNames[1] == "001");
   CPPUNIT_ASSERT(headerVarNames[2] == "011");
   CPPUNIT_ASSERT(headerVarNames[3] == "010");
   CPPUNIT_ASSERT(headerVarNames[4] == "110");
   CPPUNIT_ASSERT(headerVarNames[5] == "111");
   CPPUNIT_ASSERT(headerVarNames[6] == "101");
   CPPUNIT_ASSERT(headerVarNames[7] == "100");
   CPPUNIT_ASSERT(headerVarNames.size() == 8);

   DataBackend defaultTT6vars(6); //defaultvariables A,B,C,D,E,F
   CPPUNIT_ASSERT(defaultTT6vars.getHorizontalTitle() == "A,B,C");
   headerVarNames = defaultTT6vars.getHorizontalKMapHeader();
   CPPUNIT_ASSERT(headerVarNames[0] == "000");
   CPPUNIT_ASSERT(headerVarNames[1] == "001");
   CPPUNIT_ASSERT(headerVarNames[2] == "011");
   CPPUNIT_ASSERT(headerVarNames[3] == "010");
   CPPUNIT_ASSERT(headerVarNames[4] == "110");
   CPPUNIT_ASSERT(headerVarNames[5] == "111");
   CPPUNIT_ASSERT(headerVarNames[6] == "101");
   CPPUNIT_ASSERT(headerVarNames[7] == "100");
   CPPUNIT_ASSERT(headerVarNames.size() == 8);
   
}

void KMapperTest::minimizeBackend(){
   std::cout << std::endl << "Checking all different"
	     << "  combinations of minTerms for variables 2 to 4"
	     << std::endl;
//Generate all possible
   for(int j = 2; j <=4; j++){
      DataBackend TTtester(j);
      //Counts from 0 to 2^n-1 in binary
      //Use to test each case
      for(int count = 0; count < pow(2,TTtester.getTable().size()); count++){
	 QList<bool> binCount = TTtester.decToBinList(count);
	 for(int i = 0; i < binCount.size(); i++){
	    if(binCount[binCount.size()-1-i]){	      
	       TTtester.setMinTerm(i,TTVal::ONE);
	    }
	 }
	 TTtester.minimize();
      }
   }

   //If you want to take the time, try it with 5
   //6 vars are just too much time : (
}
