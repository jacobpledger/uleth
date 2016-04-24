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

/********************************************************************//**
\file
\brief Implementation file for the DataBackend class
%
\date Feb 17, 2010
\author Brian, Johnny, Nathan, Curtis B
**********************************************************************/

#include<iostream>
#include <QFile>
#include <QTextStream>
#include <math.h>
#include "DataBackend.h"
#include "EquationParser.h"

/********************************************************************
public
**********************************************************************/

/**
   Constructor that sets the  initial number of variables.
   
    \param numOfVars The number of variables the DataBackend will have.
*/
DataBackend::DataBackend(int numOfVars){
  SOPResult="";
  POSResult="";
  setNumVars(numOfVars);
}


/**
   Exports a .pla file

   See importFile for details of file formatting
   
 \param outFileName The name of the file to write to.
 \return Returns whether or not the File succesfully exported. 1=successful
*/
//  Note: Exceptions not checked for yet.
bool DataBackend::exportFile(const QString& outFileName) const{
   QFile outFile(outFileName);
      
   if (!outFile.open(QIODevice::WriteOnly)){
      std::cerr << "ERROR: File "
		<< outFile.fileName().toAscii().data()
		<< " could not be opened to read."
		<< std::endl;
      return false;
   }
   
   QTextStream outStream(&outFile); //The output file stream
   
   //number of inputs
   outStream << ".i "
	     << this->numVars
	     << '\n';
   //number of outputs
   outStream << ".o 1"
	     << '\n' << '\n';
   //variable names
   outStream << ".ilb ";

   for(int i = 0; i < this->numVars; i++)
   {
     if(i) outStream << " ";
     outStream << varNames[i];
   }
   outStream << '\n';
   
   //outputs
   outStream << ".ob f"
	     << '\n' << '\n';
   //number of lines 
   outStream << ".p " << this->numberOfMinTermsEqualsONE()
	     << '\n' << '\n';
   
   //printing 0's , 1's , and -'s
        
   for(int i=0;i<result.size();i++){
      for(int j=0;j<implicants[0].length()-1;j++)
	 outStream << implicants[result[i]-1].at(j);
      outStream << " 1\n"; 
   }  

   /*  
   for(int i = 0; i < fGroup.size(); i++){
        for(int j = 0; j < fGroup.at(i).dashVect.size(); j++)
         outStream << valueToString(fGroup.at(i).dashVect[j]);
      outStream << " 1\n";
	 
      }
   */
   outStream << '\n'
	     << ".e"
	     << '\n';
   return true; //Got here succesfully. Return true.
}


/**
   Imports a .pla file
   
   Warning: only 1 output variable handled.
   '-' is handled
   E.G. .pla
   .i 3          <-- Number of Input Variables (needed)
   .o 1          <-- Number of output variables (optional for import)
   .ilb a b c    <-- Input Variable names (needed)
   .ob f         <-- Output Signal name (optional for import)
   .p 3          <-- Number of terms in truth table (optional for import)
   001 1         <-- Next three lines are needed
   010 0
   101 1
   .e             <-- End of file(needed)
  Standard taken from http://www.cs.columbia.edu/~cs4861/sis/pla.txt and
  faculty.kfupm.edu.sa/coe/aimane/coe561/sis_fileformats.pdf
  with a few minor alterations. (accessed Feb 19, 2010)
  \param inFileName The name of the file to read from.
  \return Returns whether or not the File succesfully imported 1=successful
*/
bool DataBackend::importFile(const QString& inFileName) {
   
  
   //Open file
   QFile inFile(inFileName);
   if(!inFile.open(QIODevice::ReadOnly)){
      std::cerr << "ERROR: File "
		<< inFile.fileName().toAscii().data()
		<< " could not be opened to read."
		<< std::endl;
      return false;
   }
  
   QTextStream inStream(&inFile); //Create file stream for file
   QString text = "";             //The text we are reading in

   
   //Read number of variables
   inStream >> text;
		       

   if(text == ".i"){
      int numOfVars;
      inStream >> numOfVars;
      if(numOfVars > MAX_NUM_VARS){
	 std::cerr << "ERROR: File "
		   << inFile.fileName().toAscii().data()
		   << " had " << numVars << " variables when the maximum ammount allowed is "
		   << MAX_NUM_VARS << ". This software is actually expandable and could handle your"
		   << " number of variables (with computation overhead). Please contact developer to"
		   << " update this if needed."
		   << std::endl;
	 return false;
      }
      else if(numOfVars<MIN_NUM_VARS){
	 std::cerr << "ERROR: File "
		   << inFile.fileName().toAscii().data()
		   << " had " << numVars << " variables when the minimum ammount allowed is "
		   << MIN_NUM_VARS << std::endl;
	 return false;
      }
      else{
	 setNumVars(numOfVars);
      }
   }
   else{
      std::cerr << "ERROR: File "
		<< inFile.fileName().toAscii().data()
		<< " did not start with .i [NUMBER_OF_INPUT_VARIABLES]"
		<< std::endl;
      return false;
   }
   //Read number of output variables
   inStream >> text;
   int numberOfOutputVariables = 1; //Number of Output Variables. This should only be 1
                                    //for this project. Will be 1 by default if not specified.

   if(text == ".o"){     
      inStream >>  numberOfOutputVariables;
      if(numberOfOutputVariables == 1){
	 //Do nothing. This is what we expect.
      }
      else{
	 std::cerr << "WARNING: More than one output variable specified, but current"
		   << " version only supports one output variable. Only the first output"
		   << " variable will be used."
		   << std::endl;
	 //Do nothing. We only want to use 1 output variable
      }
   }
   else{
      std::cerr << "WARNING: Number of output variables not specified. Assuming only 1 is used."
		<< std::endl;
      //Do nothing. We only want to use 1 output variable
   }

   //Read input variable names
   inStream >> text;
   QList<QString> inputVariableNames;
   if(text == ".ilb"){
      for(int i = 0; i < this->numVars; i++){
	 QString inputName;
	 inStream >> inputName;
	 if(inputName.size() <= 2){ //Magic number! should be global constant...
	    inputVariableNames.push_back(inputName.toAscii().data());
	 }
	 else{
	    std::cerr << "Error, variable name " << inputName.toAscii().data()  << " was read. Variable names "
		      << "may only be 2 characters long." << std::endl;
	    return false;
	 }
      }
      
      this->varNames = inputVariableNames;
   }
   else{
      std::cerr << "ERROR: File "
		<< inFile.fileName().toAscii().data()
		<< " did not contain .ilb specifying the variable names in the proper .pla formatting scheme"
		<< std::endl;
      return false;
   }

   //Read output Signal name, but don't use it as we don't need it.
   inStream >> text;;
   if(text == ".ob"){
      for(int i = 0; i < numberOfOutputVariables; i++){
	 inStream >> text; //But don't use this
      }
      inStream >> text; //Get next string
   }
   else{
      std::cerr << "WARNING: Output Signal name not specified, but not used anyways."
		<< std::endl;
   }

   //Read number of product terms, but we don't care because we count them
   // as we just push them onto our Truth Table as we read them
   if(text == ".p"){
      inStream >> text; //Get but don't use numbers
      inStream >> text; //Get next string
   }
   else{
      std::cerr << "WARNING: Number of product terms not specified, but not used anyways."
		<< std::endl;
   }

   //Read in Truth TAble
   vectorAllMinterms.resize(0);
   QVector<QVector<TTVal::TYPE> > InputTruthTable;
   //For each string in.pla flie
   while (text != ".e" || inStream.atEnd() == 1) { //Check for atEnd so if no .e we won't be in infinite loop

     //Check length of the string
     if(text.size() != this->numVars){
	 std::cerr << "ERROR: Number of variables read in row in truth table is " << text.size()
		   << " and number of variables is " << numVars << std::endl;
	 std::cerr << text.toAscii().data() << std::endl;
	 return false;
     }

      
      int numDashes = 0;//Number of dashes in the string
      //Count dashes in the string
      for(int i=0; i<=this->numVars; i++){
	 if(text[i]=='-'){
	    numDashes++;
	 }
      }
      
     
      int sizeTempVector = 0;//number of minterms for the string
      if(numDashes>0){
	 sizeTempVector =(int)pow(2,this->numVars);
      }
      else{
	 sizeTempVector = 1;
      }
      tempVector.resize(0);

      

     //Fill in the tempVector with the possibilities for the first sybmol
     int halfRows = sizeTempVector;//for symbol itteration
     if(text[0]=='1' || text[0]=='0'){
	
	for(int n=0; n<sizeTempVector;n++){
	   QChar str = text[0].toAscii();
	   tempVector.push_back(str);
	}
     }
     else if(text[0]=='-'){
        halfRows =halfRows/2;
	for(int n=0;n<halfRows;n++){
	   tempVector.push_back("0");	   
	}
	for(int n = halfRows;n<sizeTempVector;n++){
	   tempVector.push_back("1");
	}

     }
     else{
	std::cerr << "ERROR: Wrong symbol in the file" << std::endl;
	return false;
     }
     

     
     //Fill in the tempVector with the possibilities for the  rest input symbols
     for(int i=1; i<numVars;i++){
	
	if(text[i] =='1' || text[i]=='0'){
	   QChar strnext = text[i].toAscii();
	   for(int n=0; n<sizeTempVector;n++){
	      tempVector[n]=tempVector.at(n)+strnext;
	   }
	}
	else if(text[i] == '-'){
  	   halfRows = halfRows/2; // For more freaquent itterations
	   QString zero="0";
	   QString one ="1";

	   
	   for(int n=0; n<sizeTempVector;n++){

	      //start with 0 symbol
	      int nextpart1 =halfRows+n;	      
	      for(int m=n; m<nextpart1; m++){
		 tempVector[n]=tempVector.at(n)+zero;
		 n=n+1;
	      }
	   
	      //next itteration is 1s
	      int nextpart2 = halfRows+n;	      
	      for(int m=n;m<nextpart2;m++){
		 tempVector[n]=tempVector.at(n)+one;
		 n=n+1;
		 if(n==sizeTempVector) break;
	      }
	      n=n-1;
	 
      
	   }
	}
	else{
	   std::cerr << "ERROR: Wrong symbol in the file" <<std::endl;
	   return false;
	}
     }

     
       
     //Add the second column symbol into the tempVector
     QString secondColumnInput;
     inStream >> secondColumnInput;

     if(secondColumnInput[0].toAscii()=='0' || secondColumnInput[0].toAscii()=='1' || secondColumnInput[0].toAscii()=='x' || secondColumnInput[0].toAscii()=='X'){
	for(int n=0; n<sizeTempVector;n++){
	   tempVector[n]= tempVector[n]+ " "+ secondColumnInput[0].toAscii();
	}
     }
     else{
	std::cerr << "WARNING: File" << inFile.fileName().toAscii().data()
		  << "contains truth table with values that are not a 0, 1 or X."
		  << " These values were ignored." << std::endl;
	return false;
     }


    
     //Insert tempVector's string into the vectorAllMinterms(vector of all strings from .pla file)
     for(int n=0; n<sizeTempVector;n++){

	bool foundsameinput = false;
	bool foundsameoutput = false;

	QString firstcol;
	//Get first column part of the string
	for(int k=0; k<numVars;k++){
	   firstcol.append(tempVector.at(n));
	}
	
	//Check if such string already exists inside vectorAllMinterms if not add it to the vectorAllMinterms
	for(int m=0; m<vectorAllMinterms.size();m++){
	   //Check for the same first column
	   QString tempstring = tempVector[n];
	   if(vectorAllMinterms[m].startsWith(tempstring)){
	      foundsameinput = true;
	      //Check for the same second column
	      if(vectorAllMinterms[m].endsWith(tempstring.at(tempstring.size()-1))){
		 foundsameoutput = true;
	      }
	   }
	}
	
	//not found
	if(foundsameinput == false && foundsameoutput == false){
	   vectorAllMinterms.push_back(tempVector.at(n));
	}
	//found same first column, but different second column
	else if(foundsameinput == true && foundsameoutput == false){
	   std::cerr << "WARRING: File " << inFile.fileName().toAscii().data()
		     << " contains truth table with inconsistent date" <<std:: endl;
	   return false;
	}
     }

     //read next string from .pla file
     if(!inStream.atEnd())
	inStream >> text; 
   }


   
   //Read strings from vectorAllMinterms to the primary Truth Table vector
   for(int i= 0; i<vectorAllMinterms.size();i++){
      
      QString input = vectorAllMinterms[i].left(numVars);
      QChar output = vectorAllMinterms[i].at(vectorAllMinterms[i].size()-1);

      if(output=='0') this->setMinTerm(input,TTVal::ZERO);
      else if(output =='1') this->setMinTerm(input,TTVal::ONE);
      else if(output == 'x'|| output == 'X') this->setMinTerm(input,TTVal::DONT_CARE);
      else{
	 break;
      }
   }


      
   return true; //Got here succesfully. Return true.
}



/**
   Get the number of rows and columns in K-Map representation

   \param [out] nRows The number of rows in the KMap-formatted data
   \param [out] nCols The number of columns in the KMap-formatted data
*/
void DataBackend::getKMapSize(int& nRows, int& nCols) const{
   nCols = nRows = (int)pow(2,numVars/2);
   if(numVars % 2 == 1){
      nCols *= 2;
   }			
}

/**
   Get the size of the stored truth table.

   \param [out] nRows The number of rows in the truth table
   \param [out] nCols The number of columns in the truth table
   \return the size of the truth table.
*/
void DataBackend::getTruthTableSize(int& nRows, int& nCols) const{
  nRows = backendTruthTable.size();
  if(nRows>0)
    nCols = backendTruthTable[0].size();
  else
    nCols=0;
}

/**
   Provide the horizontal KMap header
   
   \return The horizontal kmap header.  Ex: {00, 01, 11, 10}
*/
QList<QString> DataBackend::getHorizontalKMapHeader() const{
   QList<QString> headerNames;
   int numColVars = numVars/2 + numVars % 2;
   int nCols = 2;  //Initiallized to 2 just incase
   int dummyNRows = 0; //Don't need this
   getKMapSize(dummyNRows, nCols);

   //Build names
   for(int i = 0; i < nCols; i++){
      int greyCodeCount = i^(i >> 1); //Converts to grey code
      QString name = decToBin(greyCodeCount);

      //Push 0s on the front of string
      int nameSize = name.size();
      while(nameSize++ < numColVars){
	 name.push_front("0");
      }

      headerNames.push_back(name);
   }
   
   return headerNames;

}


/**
   Provide the vertical KMap header

   \return The vertical kmap header.  Ex: {~Q~R, ~QR, QR, Q~R}
*/
QList<QString> DataBackend::getVerticalKMapHeader() const {
   QList<QString> headerNames;
   int numRowVars = numVars/2;
   int dummyNCols = 0;  //Don't need this
   int nRows = 2;  //Initiallized to 2 just incase
   getKMapSize(nRows, dummyNCols);

      //Build names
   for(int i = 0; i < nRows; i++){
      int greyCodeCount = i^(i >> 1); //Converts to grey code
      QString name = decToBin(greyCodeCount);
      
      //Push 0s on the front of string
      int nameSize = name.size();
      while(nameSize++ < numRowVars){
	 name.push_front("0");
      }

      headerNames.push_back(name);
   }

   return headerNames;

}

/**Provide the horizontal title for the KMap

  \return The KMap horizonal header. EX: (ABC)
*/
QString DataBackend::getHorizontalTitle() const{
   int numColVars = numVars/2 + numVars % 2;
   QString title = "";
   for(int i = 0; i < numColVars; i++){
     if(i) title.append(",");
     title.append(varNames[i]);
   }
   return title;
}

/**Provide the vertical title for the KMap
  \return The KMap horizonal header. EX: (DE)
*/
QString DataBackend::getVerticalTitle() const{
   int numColVars = numVars/2 + numVars % 2;
   QString title = "";
   for(int i = numColVars; i < numVars; i++){
     if(i!=numColVars) title.append(",");
     title.append(varNames[i]);
   }
   return title;
}

   int DataBackend::maxImplicant(QVector<QVector<int> > &table)
{
   int location=0 , sum=0 , max=0;
   for(int i=1;i<table[0].size();i++)
   {
      for(int k=1;k<table.size();k++)
      {
	 sum +=table[k][i];
      }
      if(sum>max)
      {
	 max=sum;
	 location=i;
      }
      sum=0;
   }
   return location;
}

//finds an element in the list
int DataBackend::find(int element,QVector<QVector<int> > list)
{
   for(int i=1;i<list.size();i++)
   {
      if(list[i][0]==element)
      {
	 return i;
      }
   }
   return 0;
}

//converts numbers to binary strings to be used in the primeImplicants function
QString DataBackend::binary(int number, int length)
{
   QString bin="";
   for(;number>0;) //divides the number by two until it reaches zero, adding
   {               //ones and zeros to the binary string
      bin+=char(number%2+'0');
      number/=2;
   }
   while(bin.size()<length) //add zeros to the end of the string until it is 
   {
      bin+='0';
   }
//the right length
   QString bin2;
   for(int i=bin.size()-1;i>=0;i--)//reverse the string
   {
      bin2+=bin[i];
      
   }
   return bin2;
}

/**
 Minimize function.

 Applies the Quine–McCluskey to find minimal SOP and POS form of the given
 data set.  Results are stored internally.
 \param int to determine 1 SOP or 2 POS (if not 0 or 1 assumes 1) 
 \post POSResult and SOPResult are set to the minimized result of current data
*/
void DataBackend::minimize(TTVal::TYPE in)
{  

   //Ensure vailid input
   if(in != TTVal::ZERO && in != TTVal::ONE)
      in = TTVal::ONE;
   if(in == TTVal::ONE){
      SOP =true;
      SOPResult = "";
   }
   else{
      SOP =false;
      POSResult ="";
   }

   //Color full map blank
   numOfTimes.clear();
   numOfTimes.fill(0, backendTruthTable.size());
   
   //Handle base cases
   if(numberOfMinTermsEqualsONE() == 0){
      SOPResult = "0";
      POSResult = "0";
      return;
   }
   if( numberOfMinTermsEqualsZERO() == 0){
      numOfTimes.clear();
      numOfTimes.fill(1, backendTruthTable.size());
      SOPResult = "1";
      POSResult = "1";
      return;
   }


   
   int size=numVars;
   mintermArray.clear();
   implicants.clear();
   int num = 1;
   for(int i = 0; i < size; i++)
   {
      num = num*2;
   }
   for(int i = 0; i < num; i++)
   {
      if(getMinTerm(i) == TTVal::DONT_CARE)
      {
	 mintermArray.push_back(2);
      }
      else
	 if(getMinTerm(i) == TTVal::ONE)
	 {
	 mintermArray.push_back(1);
	 }
	 else
	    if(getMinTerm(i) == TTVal::ZERO)
	    {
	       mintermArray.push_back(0);
	    }
   }
   for(int i = 0; i < num; i++)
   {
      implicants.push_back(binary(i,size));
   }
   if(!SOP) //if not SOP, switch ones to zeros and zeros to ones
   {
      for(int i=0;i<mintermArray.size();i++)
      {
	 if(mintermArray[i] == 0)
	 {
	    mintermArray[i] = 1;
	 }
	 else if(mintermArray[i] == 1)
	 {
	    mintermArray[i] = 0;
	 }
      }
   }
   
   size = implicants[0].size();         //number of variables
   
   
   QVector<QString> newImplicants, newImplicants2;     //vector to store temporary
   QVector<QVector<int> > minterms, minterms2;         //values used for
   QVector<int> temp;                                 //calcluations

   int same;            //int to compare implicants
   bool matched;    //true if the implicant was not combined with another
   bool repeat;         //true if we have to loop again

   temp.push_back(0);

   //move any implicants with either a 1 or a don't care value into
   //new QVectors to be used in calculating the prime implicants
   for(int i=0;i<implicants.size();i++)
   {
      if(mintermArray[i]!=0)
      {
	 newImplicants.push_back(implicants[i]);
	 temp[0] = i;
	 minterms.push_back(temp);
      }
   } 


   do
   {
      repeat = false;  //assume that we will be done after this iteration

      //look for matching implicants in the vector
      for(int i=0;i<newImplicants.size();i++)
      {
	 //if the implicant's size is greater than the number of variables
	 //skip it
	 if(static_cast<int>(newImplicants[i].size())>size)
	 {
	    newImplicants2.push_back(newImplicants[i]);
	    minterms2.push_back(minterms[i]);
	    continue;
	 }
	 matched = false;  

	 //compare each implicant to the current one
	 for(int j=i+1;j<newImplicants.size();j++)
	 {

	    //if the implicant's size is greater than the number of 
	    //variables, skip it
	    if(static_cast<int>(newImplicants[j].size())>size)
	    {
	       continue;
	    }

	    same = 0;
	    //count how many characters are similar between the two implicants
	    for(int k=0;k<size;k++)
	    {
	       if(newImplicants[i][k]==newImplicants[j][k])
	       {
		  
		  same++;
	       }
	    }

	    //if the implicants differ by only one character, change
	    //that character to - and move it to the second QVector
	    if(same==size-1)
	    {
	       matched = true;  
	       newImplicants2.push_back(newImplicants[i]);
		 
	       for(int k=0;k<size;k++)
	       {
		  if(newImplicants[i][k]!=newImplicants[j][k])
		  {
		     newImplicants2[newImplicants2.size()-1][k]='-';
		  }
	       }
		 
	       //add the minterms from the first implicant to the new QVector
	       minterms2.push_back(minterms[i]);
		 
	       //add the minterms from the second implicant to the new QVector
	       for(int k=0;k<minterms[j].size();k++)
	       {
		  minterms2[minterms2.size()-1].push_back(minterms[j][k]);
	       }
	    }
	 }
	  
	 //check all the implicants lower than the current one to see if they
	 //match. if they do, do not copy it to the second QVector again 
	 for(int j=0;j<i;j++)
	 {
	    if(static_cast<int>(newImplicants[j].size())>size)
	    {
	       continue;
	    }
	    same = 0;
	    for(int k=0;k<size;k++)
	    {
	       if(newImplicants[i][k]==newImplicants[j][k])
	       {
		  same++;
	       }
	    }

	    if(same==size-1)
	    {
	       matched = true; 
	    }
	 }
	 //if noneMatched is true, then the implicant cannot be combined with
	 //any others.  Add a * to the end and move it to the second QVector
	 if(!matched)  //ToDo: negative boolean
	 {
	    newImplicants2.push_back(newImplicants[i]+'*');
	    minterms2.push_back(minterms[i]);
	 }	  
      }

      //clear the implicant and minterm QVectors
      newImplicants.clear();
      minterms.clear();

      //move all the implicants from the second QVector back to the first
      for(int i=0;i<newImplicants2.size();i++)
      {
	 newImplicants.push_back(newImplicants2[i]);
      }
      //move all the minterms from the second QVector back to the first
      for(int i=0;i<minterms2.size();i++)
      {
	 minterms.push_back(minterms2[i]);
      }

      //clear the second implicant and minterm QVectors
      newImplicants2.clear();
      minterms2.clear();

      //check to see if there are any implicants that do not have a * added
      //to the end.  if there are any, then we have to do another iteration, so
      //set repeat to true
      for(int i=0;i<newImplicants.size();i++)
      {
	 if(static_cast<int>(newImplicants[i].size())==size)
	 {
	    repeat = true;
	 }
      }
      
      //remove any duplicates in the arrays of implicants and minterms
      for(int i=0;i<newImplicants.size();i++)
      {
	 for(int j=i+1;j<newImplicants.size();j++)
	 {
	    if(newImplicants[i]==newImplicants[j])
	    {
	       newImplicants.erase(newImplicants.begin()+j);
	       minterms.erase(minterms.begin()+j);
	       j--;
	    }
	 }
      }
   }
   while(repeat);
   //remove any elements of the two QVectors that are repeated
   //make sure the finalMintermArray is empty
   finalMintermArray.clear();
   implicants.clear();
   
   //move all the minterms into finalMintermArray
   for(int i=minterms.size()-1;i>=0;i--)
   {
      finalMintermArray.push_back(minterms[i]);
      implicants.push_back(newImplicants[i]);
   }
   //ToDO: make sure the implecants are in reverse order aswell
   
   //empty all the QVectors before returning from the function
   minterms.clear();
   temp.clear();
   newImplicants.clear();
   
   QVector<int> vectorTemp;   //temporaray QVector used to initialize table
   QVector<QVector<int> > table;   //table of all prime implicants and which relevant minterms they cover
   QVector<int> essential;   //list of essential prime implicant's location in finalMintermArray
   result.clear();
   vector<int> mintermImp;
   
   size = 1;
   for(int i = 0; i < numVars; i++)
   {
      size = size*2;
   }
   for(int i=0;i<size;i++)
      mintermImp.push_back(0);
   int tempInt=0;   //used in a couple areas to make code more readable

   
   vectorTemp.clear();
   vectorTemp.push_back(0);
   table.push_back(vectorTemp);
   vectorTemp.clear();
   //add a row for each minterm containing a 1(ignore dont cares)
   for(int i=0;i<mintermArray.size();i++)
   {
      if(mintermArray[i] == 1)
      {
	 vectorTemp.push_back(i);
	 table.push_back(vectorTemp);
	 vectorTemp.clear();
      }
   }
   //add a column for each prime implicant
   for(int i=1;i<finalMintermArray.size()+1;i++)
   {
      table[0].push_back(i);
   }
   //fill table with 0's
   for(int i=1;i<table.size();i++)
   {
      for(int j=0;j<finalMintermArray.size();j++)
      {
	 table[i].push_back(0);
      }
   }
   
   //put 1s in the table to represent which prime implicants cover which minterms
   for(int i=0;i<finalMintermArray.size();i++)
      for(int j=0;j<finalMintermArray[i].size();j++)
      {
	 tempInt = find(finalMintermArray[i][j],table);
	 if(tempInt !=0)
	 {
	    table[tempInt][i+1]=1;
	    mintermImp[finalMintermArray[i][j]]++;
	 }
      }
   tempInt=0;
   
   //find which minterms are only covered by 1 prime implicant
   essential.clear();
   for(int i=0;i<64;i++)
   {
      if(mintermImp[i]==1)
      {
	 essential.push_back(i);
      }
   }

   //remove the row of each essential minterm and any other rows covered by the implicant that contains that essential minterm
   //store that implicant's # in the result QVector
   for(int i=0;i<essential.size();i++)
   {
      for(int j=1;j<table[0].size();j++)
      {
	 tempInt = find(essential[i],table);
	 if(tempInt!=0 && table[tempInt][j]==1)
	 {
	    result.push_back(table[0][j]);
	    //remove the implicant from that column
	    table[0].erase(table[0].begin()+j);
	    int k=1;
	    while(k<table.size())
	    {
	       //remove the row if covered else the element in that column
	       if(table[k][j]==1)
	       {
		  table.erase(table.begin()+k);
	       }
	       else
	       {
		  table[k].erase(table[k].begin()+j);
		  k++;
	       }
	    }
	    
	 }
      }
   }
   tempInt=0;

   //if the table is not empty continue to remove the implicant that covers the most minterms until none remain
   //store that implicants # in the result QVector
   if(table.size()>1)
   {
      do
      {
	 tempInt=maxImplicant(table);
	 result.push_back(table[0][tempInt]);
	 table[0].erase(table[0].begin()+tempInt);	
	 int k=1;
	 while(k<table.size())
	 {
	    if(table[k][tempInt]==1)
	    {
	       table.erase(table.begin()+k);
	    }
	    else
	    {
	       table[k].erase(table[k].begin()+tempInt);
	       k++;
	    }
	 }
      }
      while(table.size()>1);
   }

   tempInt=0;

   vectorTemp.clear();

   for(int y=0;y<result.size();y++)
   {
      for(int i=0;i<finalMintermArray[result[y]-1].size();i++)
      {
	 numOfTimes[finalMintermArray[result[y]-1][i]]++;
      }
   }

   
   //TODO : test conversion of answer to a QString // possibly move it to another function.


   if(SOP)
   {
      int counter=0;
      for(int i=0;i<result.size();i++)
      {
	 if(i != 0)
	 {
	    SOPResult += "+";
	 }
	 for(int j=0;j<implicants[0].length();j++)
	 {

	    if(implicants[result[i]-1].at(j) == '1')
	    {
	       if(counter!=0)
		  SOPResult +="*";
	       counter++;
	       SOPResult += varNames[j];
	    }
	    else if(implicants[result[i]-1].at(j) == '0')
	    {
	       if(counter!=0)
		  SOPResult +="*";
	       counter++;
	       SOPResult += varNames[j] + "'";
	    }
	 }
	 counter =0;
      }
   }
   else
   {
      int counter =0;
      for(int i=0;i<result.size();i++)
      {
	 if(counter!=0)
	    POSResult += "*";
	 counter=0;
	 POSResult += "(";
	 for(int j=0;j<implicants[0].length();j++)
	 {
	    if(implicants[result[i]-1].at(j) == '1')
	    {
	       if(counter !=0)
	       {
		  POSResult += "+";
	       }
	       counter++;
	       POSResult += varNames[j] + "'";
	    }
	    else if(implicants[result[i]-1].at(j) == '0')
	    {
	       if(counter !=0)
	       {
		  POSResult += "+";
	       }
	       counter++;
	       POSResult += varNames[j];
	    }
	 }

	 POSResult += ")";
      }
   }

   //TESTING
   //std::cout << getSOPMinTerms().toAscii().data() << std::endl;
   //std::cout << getPOSMaxTerms().toAscii().data() << std::endl;
   //std::cout << "test POS: " << POSResult.toAscii().data() << std::endl;
   //std::cout << "test SOP: " << SOPResult.toAscii().data() << std::endl;
   //std::cout << "testING" << std::endl;
   
}

/**
   MinimizeBoth function

   Calls the minimize() funtion to compute both SOP and Pos
*/
void DataBackend::minimizeBoth(){
   minimize(TTVal::ZERO);
   minimize(TTVal::ONE);
}

/**
   Converts to Sum of Products. Helper function for minimize()
   Just converts to the product to be summed with other products
   \param values The TTVal representation of the variables
   \return Returns a string representing the sum
*/
QString DataBackend::toSop(QVector<TTVal::TYPE> values) const{
   QString sop;
   for(int i = 0; i < values.size(); i++){
      switch(values[i]){
	 case TTVal::ONE:
	    sop += varNames[i];
	    sop += "*";
	    break;
	 case TTVal::ZERO:
	    sop += varNames[i];
	    sop += "'";
	    sop += "*";
	    break;
	 case TTVal::DASH:
	 default:
  	    break;	    
      }
   }
   if(sop.endsWith("*")){
      sop.remove(sop.size()-1,1);
   }
   return sop;
}

/**
   Converts to Product of sums. Helper function for minimize()
   Just converts to the sum to be multiplied with other sums
   \param values The TTVal representation of the variables
   \return Returns a string representing the product
*/
QString DataBackend::toPos(QVector<TTVal::TYPE> values) const{
   QString pos;
   for(int i = 0; i < values.size(); i++){
      switch(values[i]){
	 case TTVal::ONE:	    
	    pos += varNames[i];
	    pos += "'";
	    pos += "+";
	    break;
	 case TTVal::ZERO:
	    pos += varNames[i];
	    pos += "+";
	    break;
	 case TTVal::DASH:
	 default:
	    break;
      }
      
   }
   if(pos.endsWith("+")){
      pos.remove(pos.size()-1,1);
   }
   return pos;
}

///Provides a QString for sum of minterms
QString DataBackend::getSOPMinTerms() const{
   QString posMin; //the minTerms part
   QString dCMin; //the dont cares part
   // posMin and dCMin will be concatenated then returned
   int nRows, nCols;
   getTruthTableSize(nRows, nCols);
   QString tmpString;
   for(int i = 0; i < nRows;  i++)
   {
      if(getMinTerm(i) == TTVal::ONE)
      {
	 if(posMin.size()>0) posMin += ", ";
	 posMin += tmpString.setNum(i);
      }
      else if(getMinTerm(i) == TTVal::DONT_CARE)
      {
	 if(dCMin.size()>0) dCMin += ", ";
	 dCMin += tmpString.setNum(i);
      }
   }
   posMin="m("+posMin+")";
   dCMin=" + d("+dCMin+")";
      
   posMin += dCMin;

   return posMin;
}

///Provides a Qstring for product of maxterms
QString DataBackend::getPOSMaxTerms() const{
   QString sopMax; //the minTerms part
   QString dCMax; //the dont cares part
   // posMin and dCMin will be concatenated then returned
   int nRows, nCols;
   getTruthTableSize(nRows, nCols);
   QString tmpString;
   for(int i = 0; i < nRows;  i++)
   {
      if(getMinTerm(i) == TTVal::ZERO)
      {
	 if(sopMax.size()>0) sopMax += ", ";
	 sopMax += tmpString.setNum(i);
      }
      else if(getMinTerm(i) == TTVal::DONT_CARE)
      {
	 if(dCMax.size()>0) dCMax += ", ";
	 dCMax += tmpString.setNum(i);
      }
   }
   sopMax="M("+sopMax+")";
   dCMax=" + d("+dCMax+")";
      
   sopMax += dCMax;

   return sopMax;
}
   

/**
   Function that will count the number of unique addition to final groupings.

   Loops through min, and counts the number of occurances of unique minterms
   that have not been included in the minimization yet.
   \param min Used to check against the intVect p and count the number of
   intersecting values.
   \param p Used to see how many intersecting values in this intVect are in
   min
   \post Returns the number of intersecting values between the two parameters.
*/
int DataBackend::numMinCovered(QVector<int> & min, pairPone p)
{
   QVector<int>::iterator it;
   int counter=0;
   for(it=min.begin(); it!=min.end(); it++)
   {
      if(p.intVect.contains(*it))
      {
	 counter++;
      }else{}
   }
   return counter;
}


/**
   Function that will minimize a step on call.

   Applies the QM algorithm to a QVector<pairPone> until the
   groupings contain no more possible combinations.
   \param in List of pairPones be minimized one step.
   \param unchecked List of items that where not included in result.
   \param result List of elements at the current stage.
   
   
*/
bool DataBackend::generalMin(QVector<pairPone> in,
			     QVector<pairPone> &unchecked,
			     QVector<pairPone> &result)
{
 
   // Temporary grouping vector, also initialized here
   QVector<QVector< pairPone> > group;
   for(int i=0; i<=numVars; i++)
   {
      QVector<pairPone> temp;
      group.push_back(temp);
   }
      
   // Group the pairPones based on number of TTVal::ONES
   for(int i=0; i<in.size(); i++)
   {
      int temp = in.at(i).chkNum();
      
      //cerr << temp << " group, gets:";
      pairPone test = in.at(i);
      /*
      for(int j=0; j<test.intVect.size(); j++)
	 std::cout << test.intVect.at(j) << " ";
      for(int j=0; j<test.dashVect.size(); j++)
	 std::cout << test.dashVect.at(j)-TTVal::ZERO;
      std::cout << "\n";
      */
      group[temp].push_back(in.at(i));
      
   }
   
   // For each group - the last, compare to the follow group.
   QVector<QVector< pairPone> >::iterator qit;
   QVector<pairPone>::iterator fVect, sVect;


   if(group.size()>1)
      for(qit=group.begin(); qit!=group.end()-1; qit++)
      {
	 
	 for(fVect=(*qit).begin(); fVect!=(*qit).end(); fVect++)
	 {
	    for(sVect=(*(qit+1)).begin(); sVect!=(*(qit+1)).end(); sVect++)
	    {
	       int locOfDiff=-1;
	       pairPone firstTemp=(*fVect);
	       pairPone twoTemp=(*sVect);
	       if(firstTemp.oneDifferent(twoTemp, locOfDiff))
	       {
		  firstTemp.merge(twoTemp,locOfDiff);
		  result.push_back(firstTemp);
	       }else
	       {
		  // To many(or no) mismatches, continue to next comparison
	       }
	    }
	 }
      }
   
   // Populate the unchecked QVector by doing a set difference
   // between input and result
   for(fVect=in.begin(); fVect!=in.end(); fVect++)
   {
      if(result.contains(*fVect))
      {
	 //do nothing
      }else
      {
	 unchecked.push_back(*fVect);
      }
   }
   
   // Return false if no combinations where possible
   return (!result.isEmpty());
   
}
			     


/**
   This inputs/parses equation and builds back end truth table
   \param inputEquation The string with the equation to parse
*/
void DataBackend::parse(const QString& inputEquation){
   EquationParser temp;
   std::vector<string> variableNames;
   for(int i=0;i<varNames.size();i++)
      variableNames.push_back(varNames.at(i).toStdString());
   std::vector<int> equationMinterms = temp.evaluate(inputEquation.toStdString(),variableNames);

   for(unsigned int i=0;i<equationMinterms.size();i++){
//      cerr << equationMinterms[i];
      if(equationMinterms[i] == 1)
         setMinTerm(i,TTVal::ONE);
      else
	 setMinTerm(i,TTVal::ZERO);
   }

}

/**
   Set method for the variable names.
   \param newNames A list of the newNames to be assigned to the table.
   \pre The number of newNames should be the same as the prexisting number of variables in the table.
*/
void DataBackend::setVarNames(const QList<QString>& newNames){
  if(newNames.size()!=numVars) return;
  varNames=newNames;
}

/**
  Set method to set the number of variables in the table.
  
  Sets the new number of variables, and rebuilds the truth table.  Any
  data in the table will be cleared, and backEndTruthTable will be
  reset to default values, as built by buildLookupTable.  
  \param n The new number of variables
  \post Data reset to normal table, variable names set to some sane default.
*/
void DataBackend::setNumVars(int n){
   if(n<MIN_NUM_VARS || n > MAX_NUM_VARS) return;
   varNames.clear();
   for(int i=0;i<n;i++){
      varNames<<QString('A'+i);
   }
   numVars=n;
   numberOfOnes=buildLookupTable(n);
}

/**
  Set method to set a minTerm in the table with a given value
  
  \param minTerm The binary value of the minTerm in the Truthtable we will set with the value
  \param value The value we will set the minTerm with.
*/
void DataBackend::setMinTerm(const QString& minTerm, TTVal::TYPE value){
   int decimalValue = binToDec(minTerm);
   setMinTerm(decimalValue, value);
}

/**
  Set method to set a minTerm in the table with a given value
  
  \param minTerm The value of the minTerm in the TruthTable we will set with the value at
  \param value The value we will set the minTerm with.
  \pre minTerm must be from 0 to # of Truth Table rows - 1. minTerm may not be a dash
*/

void DataBackend::setMinTerm(int minTerm, TTVal::TYPE value){
   //Check for dash. Shouldn't happen
   if(value == TTVal::DASH){
      std::cerr << "ERROR: minTerm attempted to be set using a TTVal::DASH. "
		<< "Attempt ignored. [found in DataBackend::setMinTerm]" << std::endl;
      return;
   }

   //Make sure minterm is within allowable range
   if(minTerm > backendTruthTable.size()-1 || minTerm < 0){
       std::cerr << "ERROR: minTerm recieved that is outside truth table "
		 << "boundaries. Attempt ignored. [found in DataBackend::setMinTerm]" << std::endl;
      return;
   }
   //Set value
   backendTruthTable[minTerm].last() = value;

}

/**
   Set minterm at row, column of KMap

   \param row Row of minterm in KMap
   \param column Column of minterm in KMap
   \param in Value to set the minterm to.
*/
void DataBackend::setMinTerm(const int& row, const int& column, const TTVal::TYPE& in){
   int minTerm = getMinTermLocation(row, column);
   setMinTerm(minTerm,in);
}

/**
   Returns the number of MinTerms in the TruthTable that equal ONE
x
  \return The number of MinTerms in the TruthTable that equal ONE
*/
int DataBackend::numberOfMinTermsEqualsONE() const{
   int count = 0;
   for(int i = 0; i < backendTruthTable.size(); i++){
      if(backendTruthTable[i].last() == TTVal::ONE){
	 count++;
      }
   }
   return count;
}

/**
   Returns the number of MinTerms in the TruthTable that equal ZERO
   
  \return The number of MinTerms in the TruthTable that equal ZERO
*/
int DataBackend::numberOfMinTermsEqualsZERO() const{
   int count = 0;
   for(int i = 0; i < backendTruthTable.size(); i++){
      if(backendTruthTable[i].last() == TTVal::ZERO){
	 count++;
      }
   }
   return count;
}

/**
  Get method to get a minTerm in the table with a given value
  
  \param row The binary value of row of the TruthTable corresponding to the minTerm.
  \return The minterm at that location
*/
TTVal::TYPE DataBackend::getMinTerm(const QString& row) const{
   int decimalValue = binToDec(row);
   return getMinTerm(decimalValue);
}

/**
  Get method to get a minTerm in the table with a given value
  
  \param row The value of row of the TruthTable corresponding to the minTerm.
  \return The minterm at that location
*/
TTVal::TYPE DataBackend::getMinTerm(int row) const{
   return backendTruthTable[row].last();
}

/**
   Get minterm at row, column of KMap

   \param row Row of minterm 
   \param column Column of minterm
   \return The minterm at that location
*/
int DataBackend::getMinTermLocation(const int& row, const int& column) const{
   int greyCodeCol = column^(column >> 1); //Converts to grey code
   int greyCodeRow = row^(row >> 1); //Converts to grey code
   int numRowVars = (numVars/2);
     
   int minTerm = (greyCodeCol << numRowVars) | greyCodeRow;

   return(minTerm);
}

/**
   Get minterm value at row, column of KMap

   \param row The row of minterm 
   \param column The column of minterm
   \return The value of the minterm at the given location
*/
TTVal::TYPE DataBackend::getMinTerm(const int& row, const int& column) const{
   int minTerm = getMinTermLocation(row, column);
   return getMinTerm(minTerm);
}

/**
   Get the decimal representation of the given binary number

   \param binString The binary value to convert to a decimal value
   \return The decimal value of the given binary number
*/
int DataBackend::binToDec(const QString& binString) const{
   int decimalValue = 0;
   for(int i = 0; i < binString.size(); i++){
      decimalValue *= 2;
      char c = binString[i].toAscii();  //This converts to char so we can do a switch on it
      switch(c){
	 case '0':
	    //Do nothing
	    break;
	 case '1':
	    decimalValue++;
	    break;
	 default:
	    std::cerr << "WARNING: minTerm Qstring provided has other data in it than 0 or 1."
		      << "Other data '" << binString[i].toAscii() <<"' ignored. [found in  DataBackend::binToDec]"
		      << std::endl;
	    break;
      }
   }
   return decimalValue;
}

/**
   Returns a String of the binary representation of the given integer

   \param decInt The value to be converted from binary to decimal
   \return  A String of the binary representation of the given integer
*/
QString DataBackend::decToBin(int decInt) const{ //Should maybe be unsigned int decInt
   QString binaryValue = "";
   do{
      if(decInt%2 == 1){
	 binaryValue.push_front("1");
      }
      else{
	 binaryValue.push_front("0");
      }
      decInt /= 2;
   } while(decInt != 0);
   
   return binaryValue;
}

/**
   Returns a List of the binary representation of the given integer

   \param decInt The value to be converted from binary to decimal
   \return  A List of the binary representation of the given integer
*/
QList<bool> DataBackend::decToBinList(int decInt) const{ //Should maybe be unsigned int decInt
   QString binString = decToBin(decInt);
   QList<bool> binList;
   //make sure that the binList starts with a value
		       
   for(int i = 0; i < binString.size(); i++){
      switch(binString[i].toAscii()){
	 case '0':
	    binList.append(false);
	    break;
	 case '1':
	    binList.append(true);
	    break;
	 default:
	    break;
      }
   }
   return binList;
}

/**
   Returns the string interpretation of TTVal::TYPE value.

   \param value The value to be interpretted.
   \return The interpreted value
*/
QString DataBackend::valueToString(TTVal::TYPE value) const{
   QString TTValueString = "";
   
   switch(value){
      case TTVal::ZERO:
	 TTValueString = "0";
	 break;
      case TTVal::ONE:
	 TTValueString = "1";
	 break;
      case TTVal::DONT_CARE:
	 TTValueString = "X";
	 break;
      case TTVal::DASH:
      	 TTValueString = "-";
	 break;
      default:
	 break;
   }

   return TTValueString;
}

/**
   Increment the minTerm at row by 1.

   Cycles through the possible values (0, 1, or X) of the minterm at the given
   row in the truth table.
   \param row The row to be incremented in the truth table.
*/
void DataBackend::increment(int row){
   if(getMinTerm(row) == TTVal::ZERO)
     setMinTerm(row, TTVal::ONE);
   else if(getMinTerm(row) == TTVal::ONE)
     setMinTerm(row, TTVal::DONT_CARE);
   else if(getMinTerm(row) == TTVal::DONT_CARE)
     setMinTerm(row, TTVal::ZERO);
}

/**
   Increment the minTerm at row,column by 1.

   Cycles through the possible values (0, 1, or X) of the minterm at the given
   row, column in the KMap.
   \param row The row in the KMap of the minterm to be incremented
   \param column The column in the KMap of the minterm to be incremented
*/
void DataBackend::increment(int row, int column){

   if(getMinTerm(row, column) == TTVal::ZERO)
      setMinTerm(row, column, TTVal::ONE);
   else if(getMinTerm(row, column) == TTVal::ONE)
      setMinTerm(row, column, TTVal::DONT_CARE);
   else if(getMinTerm(row, column) == TTVal::DONT_CARE)
      setMinTerm(row, column , TTVal::ZERO);
}

/********************************************************************
protected
**********************************************************************/

/**
   Does most of the default work for the constructor.

   Builds the initial values for the truth table, and also counts
   the number of ones for the QM algorithm grouping
   \return A vector of integers showing the number of ones for grouping.
*/
QVector<int> DataBackend::buildLookupTable(int numOfVariables)
{
   // Variables
   QVector<int> tempVect;
   int j, maxSize, tempInt=numOfVariables;
   QVector<QVector<TTVal::TYPE> > BackEndTruthTable;

   //Calulate the number of lookup elements
   if(numVars==0)
   {
      maxSize=0; //Base case #1
   }else if(numVars==1)
   {
      maxSize=1; //Base case #2
   }else
   {
      maxSize=2;
      while(tempInt>1) //Loop past base cases for all others
      {
	 maxSize*=2;
	 tempInt--;
      }
   } // End of if-else


   //Populates the lookup table up to maxSize's value
   for(int i=0; i<maxSize; i++)
   {
      QVector<TTVal::TYPE> ttVect;
      j=0;
      int y=0; // Keeps track of how many loops do-while does
      int temp = i;
      
      do
      {
	 if(temp % 2) // One found in remainder
	 {
	    y++;
	    j++;
	    ttVect.push_back(TTVal::ONE);
	 }else // Zero found in remainder
	 {
	    y++;
	    ttVect.push_back(TTVal::ZERO);
	 }
	 temp = temp / 2; // Next division
      }while(temp > 0);

      // Add extra forward TTVal::ZEROs
      for(int i=y; i<numOfVariables; i++)
	 ttVect.push_back(TTVal::ZERO);
      
      // Add the number of ones
      tempVect.push_back(j);

      // Set up a iterator and a vector for flipping
      QVector<TTVal::TYPE>::iterator it;
      QVector<TTVal::TYPE> ttVectFlip;

      // Flip ttVect
      for(it=ttVect.end()-1; it >= ttVect.begin(); it--)
	 ttVectFlip.push_back(*it);

      // Add a TTVal::ZERO to the end
      ttVectFlip.push_back(TTVal::ZERO);
      BackEndTruthTable.push_back(ttVectFlip);
      
   }
   backendTruthTable=BackEndTruthTable;
   return tempVect; 
}
