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
\brief Interface file for the DataBackend class

\date Jan 31, 2010
\author Brian, Johnny, Nathan, Curtis B
**********************************************************************/

#ifndef FILENAME_H
#define FILENAME_H

#include "KMapWidget.h"
#include "TruthTableWidget.h"
#include "TTVal.h"

#include<QList>
#include<QString>
#include<QVector>
#include<math.h>
#include<qvector.h>
#include<QString>

#define MIN_NUM_VARS 2 ///<The minimum number of variables to consider
#define MAX_NUM_VARS 10 ///<The maximum allowed number of variables in truth table

/// Struct to hold the number pairings for Quine-McCluskey algorithm
struct pairPone
{
      QVector<int> intVect; ///< Vector of ints...
      QVector<TTVal::TYPE> dashVect; ///< Vector of TTVal::TYPE
      bool checked; ///< has this pairPone been checked?

      ///Constructor
      pairPone()
      {
	 checked=false;
      }

      ///Merges with another pairPone
      void merge(pairPone & p, int locOfDiff)
      {
	 intVect+=p.intVect;
	 dashVect[locOfDiff]=TTVal::DASH;
      }

      ///Returns dashVect.count(tt)
      int chkNum(TTVal::TYPE tt=TTVal::ONE) const
      {
	 return dashVect.count(tt);
      }

      /// Returns if p is one different from this pairPone
      bool oneDifferent(pairPone p, int & locOfDiff)
      {
	 int numDiff=0;
 	 /*std::cout << intVect.at(0) << ":" << p.intVect.at(0) << " - ";
	 for(int i=0; i<dashVect.size(); i++)
	 {
	    std::cout << dashVect.at(i)-TTVal::ZERO;
	 }
	 std::cout << ":";
	 for(int i=0; i<p.dashVect.size(); i++)
	 {
	    std::cout << p.dashVect.at(i)-TTVal::ZERO;
	 }
	 std::cout << std::endl;
	 */
	 for(int i=0; i<dashVect.size(); i++)
	 {
	    if(dashVect.at(i) != p.dashVect.at(i))
	    {
	       numDiff++;
	       locOfDiff=i;
	    }
	 }
	 	    
	 if(numDiff!=1)
	 {
	    return false;
	 }else
	 {
	    return true;
	 }
      }

      /// Returns if this pairPone is equal to other pairPone
      bool operator==(pairPone p)
      {
	 return ((dashVect==p.dashVect) && (intVect==p.intVect)
		 && (checked==p.checked));
      }
      
};

/*******************************************************************//**
\brief Class for truth table data, as well as data processing tasks

This class is used for storing the internal representation of the truth 
table, as well as processing it (minimization).  This class has no 
knowledge of the client, so no code exists for ANY client here.
**********************************************************************/
class DataBackend{
 public:
  /// Constructor
  DataBackend(int numVars=2);
  /// Exports a .pla file
  bool exportFile(const QString& outFileName) const; 
  /// Imports a .pla file
  bool importFile(const QString& inFileName); 
  ///Accessor for numVariables
  int getNumVars() const { return numVars; }
  ///Accessor for POS result of minimization
  QString getPOSResult() const { return POSResult; }
  ///Accessor for SOP result of minimization
  QString getSOPResult() const { return SOPResult; }
  ///Accessor for the physical table
  QVector<QVector<TTVal::TYPE> > getTable() const { 
    return backendTruthTable; }
  ///Get the number of rows and columns in K-Map representation
  void getKMapSize(int& nRows, int& nCols) const;
  ///Get the size of the stored truth table
  void getTruthTableSize(int& nRows, int& nCols) const;
  ///Provide the horizontal KMap header
  QList<QString> getHorizontalKMapHeader() const;
  ///Provide the vertical KMap header
  QList<QString> getVerticalKMapHeader() const;
  ///Provide the horizontal title for the KMap
  QString getHorizontalTitle() const;
  ///Provide the vertical title for the KMap
  QString getVerticalTitle() const;
  ///Accessor for variable names
  QList<QString> getVarNames() const { return varNames; }
  /// Minimizes function, calls processes in order
  void minimize(TTVal::TYPE in=TTVal::ONE);
  /// Calls minimize 2 times to compute both POS and SOP
  void minimizeBoth();
  /// Function that will minimize a step on call.
  bool generalMin(QVector<pairPone> in,
		  QVector<pairPone> &unchecked,
		  QVector<pairPone> &result);
  ///Converts to Product of Sums. Helper function
  QString toPos(QVector<TTVal::TYPE> values) const;
  ///Converts to Sum of Products. Helper function
  QString toSop(QVector<TTVal::TYPE> values) const;
  ///Provides a QString for sum of minterms
  QString getSOPMinTerms() const;
  ///Provides a Qstring for product of maxterms
  QString getPOSMaxTerms() const;
  ///Returns number of minterms covered
  int numMinCovered(QVector<int> & min, pairPone p);
  /// This inputs/parses equation
  void parse(const QString& inputEquation); 
  ///Set method for the variable names
  void setVarNames(const QList<QString>& newNames);
  ///Set method to set the number of variables in the table.
  void setNumVars(int n);
  ///Set method to set a minTerm to 1 in the table
  void setMinTerm(const QString& minTerm, TTVal::TYPE value);
  ///Set method to set a minTerm to 1 in the table
  void setMinTerm(int minTerm, TTVal::TYPE);
  ///Set minterm at row, column of KMap
  void setMinTerm(const int& row, const int& col, const TTVal::TYPE&);
  ///Accessor to get the number of minTerms that equal 1
  int numberOfMinTermsEqualsONE() const;
  ///Accessor to get the number of minTerms that equal 0
  int numberOfMinTermsEqualsZERO() const;
  ///Accessor to get minTerm value in specified row of TT
  TTVal::TYPE getMinTerm(const QString& row) const;
  ///Accessor to get minTerm value in specified row of TT
  TTVal::TYPE getMinTerm(int row) const;
  ///Get minterm at row, column of KMap
  int getMinTermLocation(const int& row, const int& column) const;
  ///Get minterm value at row, column of KMap
  TTVal::TYPE getMinTerm(const int& row, const int& column) const;
  ///Converts binary QString to decimal int
  int binToDec(const QString& binString) const;
  ///Converts decimal int to binary QString
  QString decToBin(int decInt) const;
  ///Converts decimal int to boolean QList
  QList<bool> decToBinList(int decInt) const;
  ///Returns the string interpretation of TRUTH_VALUES in
  QString valueToString(TTVal::TYPE value) const;
  ///Increment the minTerm at row by 1
  void increment(int row);
  ///Increment the minTerm at row, column by 1
  void increment(int row, int column);
  ///Returns the number of times a minterm is in a group
  QVector<int> getNumberOfTimes() const {return numOfTimes;};
  protected:  
  /// Builds the lookup table for the constructor
  QVector<int> buildLookupTable(int numOfVariables);

  int numVars; ///< The number of variables.
  QVector<pairPone> fGroup;
  QList<QString> varNames; ///< The names of the variables.
  QVector<QVector<TTVal::TYPE> > backendTruthTable; ///< The values in our backend TruthTable
  QVector<int> numberOfOnes; ///< Stores the number of ones for the full table for grouping in stage one QM
  QVector<pairPone> storeOne; ///< Stores the initial pairings a long with their truth table values
  QVector<int> checkMissed; ///< Stores missed minterms from PartOne
  QString POSResult; ///< The POS result of minimization.  Defaults to empty.
  QString SOPResult; ///< The SOP result of minimization.  Defaults to empty.
  QVector<int> numOfTimes; ///< The number of times each minTerm is circled
  QVector<QString> tempVector; ///<Temprory store minterms for the string
  QVector<QString> vectorAllMinterms; ///<Store all minterms

  QVector<int> mintermArray;
  QVector<QVector<int> > finalMintermArray;
  QVector<QString> implicants;
  QVector<int> result;   //list of all implicant's locations in finalMintermArray that are to be used in the minimized result
  bool SOP;
  //! find Funtion
  /*!
    \param element, an integer argument
    \param table, QVector<QVector<int> > argument
    This function locates the given element in its remaining minterms and returns 0 if not found.
  */
  int find(int element, QVector<QVector<int> > table);
  //! maxImp Function
  /*!
    \param list, QVector<QVector<int> > argument
    This function determins the implicant which covers the most minterms.
  */
  int maxImplicant(QVector<QVector<int> > &list);
     //! binary Funtion
   /*!
     \param number, length, integer arguments
     This function creates binary representations in a given length of the number. 
   */
   QString binary(int number,int length);
};


#endif
