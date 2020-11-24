#include "bandMatrix.h"
#include <iostream>
#include <cassert>
#include <ostream>
using namespace std;

//*****************************************************************************
//Function: bandMatrix constructor
//Assumption(s): the arguments are >0
//Action(s): creates a bandMatrix variable
//*****************************************************************************

bandMatrix::bandMatrix(int d, int ubw, int lbw)
{
   //precondition: none
   //postcondition: a bandMatrix is created

   rows = d;
   uppbw = ubw;
   lowbw = lbw;
   uppsize = 0;
   lowsize = 0;

   //need this to count the number of items in the bands
   for (int i = 1; i <= uppbw; i++)
      uppsize += (rows - i);
   for (int i = 1; i <= lowbw; i++)
      lowsize += (rows - i);
   
   size = uppsize + lowsize + rows;
   element = new double[size];   
}

//*****************************************************************************
//Function: bandMatrix copy constructor
//Assumption(s): the bandMatrix is in a consistent state
//Action(s): creates a new bandMatrix as a copy of the left argument
//*****************************************************************************

bandMatrix::bandMatrix(const bandMatrix& m)
{
   //precondition: the argument is a bandMatrix in a consistent state
   //postcondition: a new matrix is created as a copy
   
   rows = m.rows;
   uppbw = m.uppbw;
   lowbw = m.lowbw;
   size = size;

   for (int i = 0; i < size; i++)
      m.element[i] = element[i];
}

//*****************************************************************************
//Function: bandMatrix deconstructor
//Assumption(s): a bandMatrix has been declared
//Action(s): deallocates memory used by bandMatrix variables from the heap
//*****************************************************************************

bandMatrix::~bandMatrix()
{
   //precondition: a bandMatrix variable has been allocated
   //postcondition: heap memory deallocated
   delete[] element;
   *element = 0;
}

//*****************************************************************************
//Function: () operator
//Assumption(s): the array contains values
//Action(s): returns the value in the array at position (i,j)
//*****************************************************************************

double bandMatrix::operator()(int i, int j) const
{
   //precondition: the matrix contains values
   //postcondition: a value from the matrix is returned
   
   return getNum(i,j);
}

//*****************************************************************************
//Function: assignment operator
//Assumption(s): the right operand contains values
//Action(s): assigns all values of a matrix to another matrix
//*****************************************************************************

bandMatrix& bandMatrix::operator=(const bandMatrix& m)
{
   //precondition: the matrix contains values
   //postcondition: the left argument becomes identical to the left argument
   if (this != &m)
   {
      delete [] element;
      rows = m.rows;
      uppbw = m.uppbw;
      lowbw = m.lowbw;
      uppsize = m.uppsize;
      lowsize = m.lowsize;
      size = m.size;
      element = new double [size];
      
      for (int i = 0; i < size; i++)
	 element[i] = m.element[i];
   }
   return *this; //allows cascaded calls
}

//*****************************************************************************
//Function: unary + operator
//Assumption(s): none
//Action(s): returns the matrix unchanged
//*****************************************************************************

bandMatrix bandMatrix::operator+() const
{
   //precondition: none
   //postcondition: the matrix is returned
   return *this;
}


//*****************************************************************************
//Function: binary + operator
//Assumption(s): the arrays have the same upper and lower bandwidth
//Action(s): adds two matrices
//*****************************************************************************

bandMatrix bandMatrix::operator+(const bandMatrix& m) const
{
   //precondition: the arrays have the same upper and lower bandwidths
   //postcondition: a new matrix is created with elements = to the sum of that
   //               of the arguments
   
   bandMatrix temp(rows, uppbw, lowbw);

   assert(rows == m.rows);
   for (int i = 0; i < size; i++)
      temp.element[i] = element[i] + m.element[i];
 
   return temp;
}

//*****************************************************************************
//Function: unary minus operator
//Assumption(s):
//Action(s): returns a matrix with all elements as the negative values
//*****************************************************************************

bandMatrix bandMatrix::operator-() const
{
   //precondition: the matrix contains values
   //postcondition: the elements of the array are the negative of their
   //               original values

   bandMatrix temp;
   temp.rows = rows;
   temp.uppbw = uppbw;
   temp.lowbw = lowbw;
   temp.uppsize = uppsize;
   temp.lowsize = lowsize;
   temp.size = size;
   
   for (int i = 0; i < size; i++)
      temp.element[i] = -element[i];
   return temp;
}

//*****************************************************************************
//Function: binary minus operator
//Assumption(s): both arrays contain values
//Action(s): returns a matrix with entries = to the difference of the
//           elements of the arguments 
//*****************************************************************************

bandMatrix bandMatrix::operator-(const bandMatrix& m) const
{
   //precondition: the arrays contain nonzero values
   //postcondition: a new matrix is returned containing the difference between
   //               the left and right arguments
   
   bandMatrix temp(rows, uppbw, lowbw);
   assert(rows == m.rows);
   for (int i = 0; i < temp.size; i++)
      temp.element[i] = element[i] - m.element[i];
   
   return temp;
}

//*****************************************************************************
//Function: multiplication operator
//Assumption(s): 
//Action(s): multiplies the elements of the two matrices
//*****************************************************************************

bandMatrix bandMatrix::operator*(const bandMatrix& m) const
{
   //precondition: rows == m.cols
   //postcondition: a matrix is returned as the multiple of the two arguments

   //this has not been edited at all from Hossain's original definition
   
   bandMatrix temp(rows);
   //positions in this, m, and temp
   int tp = 0, mp = 0, wp = 0;

   for (int i = 1; i <= rows; i++) {
      //compute row i of result
      for (int j = 1; j <= m.rows; j++) {
	 //compute element (i,j)
	 double sum =  element[tp] * m.element[mp];
	 for (int k = 1; k < rows; k++) {
	    tp++; mp += m.rows;
	    sum += element[tp] * m.element[mp];
	 }
	 //save element (i,j)
	 temp.element[wp++] = sum;
	 //reset to start of row and next column
	 tp = tp - rows + 1; mp = j ;
      }
      //reset to start of next row and first column
      tp = tp + rows; mp = 0;
   }
   return temp;
}

//*****************************************************************************
//Function: += operator
//Assumption(s): the matrix contains values
//Action(s): increments all values of the array by a constant
//*****************************************************************************

bandMatrix& bandMatrix::operator+=(const double& x)
{
   //precondition: the array contains values
   //postcondition: all elements are incremented by x
   
   for (int i = 0; i < size; i++)
      element[i] += x;
   
   return *this;
}

//*****************************************************************************
//Function: print
//Assumption(s): the matrix has values to output
//Action(s): outputs the bandMatrix to the standard output
//*****************************************************************************

void bandMatrix::print(ostream& out) const
{
   //precondition: the matrix has values to output
   //postcondition: the matrix is output in the form desired
   
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < rows; j++)
	 cout << getNum(i,j) << ' ';
      cout << endl;
   }
   cout << endl;
}

//*****************************************************************************
//Function: stream insertion operator
//Assumption(s): the matrix contains values
//Action(s): overloads the << operator for output
//*****************************************************************************

ostream& operator<<(ostream& out, const bandMatrix& x)
{
   //precondition: 
   //postcondition: 
   
   x.print(out);
   return out;
}

//*****************************************************************************
//Function: fill
//Assumption(s): 
//Action(s): gets user input to the matrix
//*****************************************************************************

void bandMatrix::fill()
{
   double temp[size]; //the compiler didn't like me directly cin-ing to dynamic
                      //memory

   cout << "Please enter the band matrix from lowest subdiagonal to highest superdiagonal: ";
   
   for (int i = 0; i < size; i++)
   {
      cin >> temp[i];
      element[i] = temp[i];
   }
}

//*****************************************************************************
//Function: getNum
//Assumption(s): the matrix contains values
//Action(s): returns the element at position i,j
//*****************************************************************************

double bandMatrix::getNum(int i, int j) const
{
   int num = 0;
   if (i == j && i < rows)
      return element[lowsize+i];
   
   else if (i > j && i-j <= lowbw)
   {
      num = lowsize;
      for (int k = 1; k <= (i-j); k++)
	 num -= (rows - k);
      return element[num + j];
   }
   else if (i - j > lowbw)
      return 0;
   
   else if (i < j && j-i <= uppbw)
   {
      num = lowsize + rows + i;
      for (int k = 1; k < (j - i); k++)
         num += (rows - k);
      return element[num];
   }
   else if (j - i > uppbw)
      return 0;
   
   return -1; //indicates error if an entry cannot be returned
              //(and causes the compiler to stop giving me warnings)
}
