#ifndef QUINEMCCLUSKEY_H
#define QUINEMCCLUSKEY_H

#include "templates.h"
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

//! typedefs for ease of use
typedef string BinaryString_t;
typedef string TruthTableString_t;
typedef unsigned int RowNumber_t;
typedef set<RowNumber_t> SetOfRowNumbers_t;
typedef map<RowNumber_t, BinaryString_t> Minterms_t;

//! A minterm (also known as a product, because it is the logical AND of a set
//! of variables) is the number of a row of a truth table evaluating to true. It
//! is stored as a pair; a row number in the truth table, and a binary string
//! representation of the truth table row's bits. Minterm binary strings are not
//! allowed to contain any values other than '0' and '1' (unlike implicants)

//! A product of sums is an boolean function derived from the combining of 

//! An implicant is a "covering" (sum term or product term) of one or more
//! minterms in a sum of products (or maxterms in a product of sums) of a
//! boolean function.

//! It is stored as a set of truth table row numbers and a single modified
//! binary string representing the combination of all rows. The digits of a
//! modified binary string can contain the digits '0', '1', and 'X', where '0'
//! indicates that the corresponding bit of all covered minterms is always
//! false, a '1' indicates that the corresponding bit of all covered minterms
//! is always true, and and 'X' indicates that the corresponding bit of all
//! covered minterms can be true or false.
//!
//! *Note*: Binary strings of length n are stored with the most significant bit
//! on the left (offset = 0), and the most significant bit on the right (offset
//! = n - 1).
//!
//! Example binary strings and their equivalent covered sets of minterms:
//! Binary string: "01X0"
//! Set of minterms: {"0100" (4), "0110" (6)}
//!
//! Binary string: "X0X11"
//! Set of minterms: {"00011" (3), "00111" (7), "10011" (19), "10111" (23)}
typedef map<SetOfRowNumbers_t, BinaryString_t> Implicants_t;
typedef unsigned int NumberOfOnes_t;
typedef map<NumberOfOnes_t, Minterms_t> InitialMinterms_t;
typedef map<NumberOfOnes_t, Implicants_t> ImplicantsWithSameNumberOfOnes_t;
typedef pair<ImplicantsWithSameNumberOfOnes_t, Implicants_t> ImplicantCombinationResult_t;

typedef vector<BinaryString_t> ProductOfSumsSum_t;
typedef vector<ProductOfSumsSum_t> ProductOfSums_t;

typedef vector<BinaryString_t> SumOfProductsProduct_t;
typedef vector<SumOfProductsProduct_t> SumOfProducts_t;

// runs the Quine-McCluskey algorithm on a truth table string and returns a minimum set of prime implicants
Implicants_t Quine_McCluskey(TruthTableString_t truth_table_string);

//! Given a truth table string, this function returns all implicants corresponding to the minterms of the product of sums
Implicants_t Generate_Implicants_From_Truth_Table_String(TruthTableString_t truth_table_string);
Minterms_t Generate_Minterms_From_Truth_Table_String(TruthTableString_t truth_table_string);
unsigned int Log_Base_2(unsigned int value);
string Generate_Binary_String(unsigned int decimal_value, unsigned int desired_string_length);
Implicants_t Convert_Minterms_Into_Implicants(Minterms_t minterms);
ImplicantsWithSameNumberOfOnes_t Group_Implicants_By_Number_Of_Ones_In_Binary_Representation(Implicants_t);
int Number_Of_Ones_In_Binary_String(const BinaryString_t &binstr);
Implicants_t Gather_Prime_Implicants(ImplicantsWithSameNumberOfOnes_t implicants);
ImplicantCombinationResult_t Combine_Implicants_Differing_By_Single_Bit(ImplicantsWithSameNumberOfOnes_t old_implicants);
BinaryString_t Combine_Binary_Strings_Differing_By_Single_Bit(BinaryString_t, BinaryString_t);
bool Binary_Strings_Differ_By_Single_Bit(BinaryString_t, BinaryString_t);
BinaryString_t::size_type Get_Offset_Of_Differing_Bit(BinaryString_t, BinaryString_t);

Implicants_t Gather_Essential_Prime_Implicants(Implicants_t, TruthTableString_t);
ImplicantsWithSameNumberOfOnes_t::iterator Get_Next_To_Last_Iterator(ImplicantsWithSameNumberOfOnes_t::iterator begin_iter, ImplicantsWithSameNumberOfOnes_t::iterator end_iter);
Implicants_t Map_Difference(Implicants_t, Implicants_t);
set<SetOfRowNumbers_t> Get_Implicants_Sets(const Implicants_t &);
Implicants_t Get_Minimum_Set_Of_Prime_Implicants(Implicants_t, TruthTableString_t);

SumOfProducts_t Petricks_Method(Implicants_t);
/*!
*Note*: This is part of Petrick's method

Given a vector of vectors of minterms stored as binary strings (each minterm is represented by a letter in this example)
((A,C),(A,B),(A,D))

Interpret it as a product of sums and convert it to a sum of products by cross multiplication and removal of duplicate products and product terms
((A+C)*(A+B)*(A+D)) -> cross multiplication
((A*A*A)+(A*A*D)+(A*B*A)+(A*B*D)+(C*A*A)+(C*A*D)+(C*B*A)+(C*B*D)) -> removal of duplicates (both inner and outer)
((A)+(A*D)+(A*B)+(A*B*D)+(C*A)+(C*A*D)+(C*B*A)+(C*B*D))
*/

vector<vector<BinaryString_t> > Convert_Petricks_Product_Of_Sums_To_Sum_Of_Products(vector<vector<BinaryString_t> > product_of_sums);

SetOfRowNumbers_t Remove_Dont_Cares(const SetOfRowNumbers_t &, const TruthTableString_t &);
SetOfRowNumbers_t Union_All_Implicant_Row_Number_Sets(const Implicants_t &);

//! given a string representing the values of truth table rows and an index of
//! variable names, returns an minimal product of sums expression string that
//! will generate that truth table rows when evaluated
Implicants_t Get_Optimal_Maxterms(TruthTableString_t truth_table_string);
string Get_POS_Expression_String(Implicants_t maxterm_implicants, vector<string> var_names);
//! given a string representing the values of truth table rows and an index of
//! variable names, returns an minimal sum of products expression string that
//! will generate that truth table rows when evaluated
Implicants_t Get_Optimal_Minterms(TruthTableString_t truth_table_string);
string Get_SOP_Expression_String(Implicants_t minterm_implicants, vector<string> var_names);

set<SetOfRowNumbers_t> Get_Set_Of_All_Implicant_Row_Number_Sets(const Implicants_t &implicants);

//! std::ostream overloaded operators
ostream & operator<<(ostream &, const Implicants_t &);
ostream & operator<<(ostream &, const ImplicantsWithSameNumberOfOnes_t &);
ostream & operator<<(ostream &, const InitialMinterms_t &);
ostream & operator<<(ostream &, const Minterms_t &);
ostream & operator<<(ostream &, const SetOfRowNumbers_t &);

// Testing functions
void Test_Convert_Product_Of_Sums_To_Sum_Of_Products(void);

#endif
