#include <cassert>
#include "matrix.h"
#include <iostream>
using namespace std;
Matrix::Matrix(int r, int c)
{//create
   rows = 0; cols = 0; // if invalid row or column create an empty matrix
   if ((r >= 0) && (c >= 0))    //  r and c both be zero or,
      if (!((r || c) && (!r || !c))) { // both be greater than zero
	 rows = r; cols = c;
	 element = new double [r * c];
      }
}
Matrix::Matrix(const Matrix& m)
{//copy constructor
   rows = m.rows; cols = m.cols;
   element = new double [rows * cols];
   //copy each element
   for (int i = 0; i < rows * cols; i++)
      element[i] = m.element[i];
}
Matrix& Matrix::operator=(const Matrix& m)
{//assignment
   if (this != &m) {//do not copy to self
      delete [] element; // return the old memory to the free store
      rows = m.rows; cols = m.cols;
      element = new double [rows * cols];
      //copy each element
      for (int i = 0; i < rows * cols; i++)
	 element[i] = m.element[i];
   }
   return *this; //  refernce return so that we can have m1 = m2 = m3 for matrices m1, m2, and m3
}
double& Matrix::operator()(int i, int j) const
{//reference to element (i,j)
   assert(i >= 0 && i < rows && j >= 0 && j < cols);
   return element[i * cols + j];
}
Matrix Matrix::operator+(const Matrix& m) const
{
   assert(rows == m.rows && cols == m.cols);
   Matrix w(rows, cols);
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = element[i] + m.element[i];
   return w;
}
Matrix Matrix::operator-(const Matrix& m) const
{
   assert(rows == m.rows && cols == m.cols);
   Matrix w(rows, cols); // temporary matrix to store the sum
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = element[i] - m.element[i];
   charreturn w;
}
// unary minus operator
Matrix Matrix::operator-() const
{
   Matrix w(rows, cols);
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = -element[i];
   return w;
}
// overloaded multiplication operator
Matrix Matrix::operator*(const Matrix& m) const
{
   assert(cols == m.rows); // check for matching dimension
   Matrix w(rows, m.cols);
   //positions in this, m, and w
   int tp = 0, mp = 0, wp = 0;
   for (int i = 1; i <= rows; i++) {
      //compute row i of result
      for (int j = 1; j <= m.cols; j++) {
	 //compute element (i,j)
	 double sum =  element[tp] * m.element[mp];
	 for (int k = 1; k < cols; k++) {
	    tp++; mp += m.cols;
	    sum += element[tp] * m.element[mp];
	 }
	 //save element (i,j)
	 w.element[wp++] = sum;
	 //reset to start of row and next column
	 tp = tp - cols + 1; mp = j ;
      }
      //reset to start of next row and first column
      tp = tp + cols; mp = 0;
   }
   return w;
}
// scalar addition
Matrix& Matrix::operator+=(const double& x)
{
   for (int i = 0; i < rows * cols; i++)
      element[i] += x;
   return *this;
}
void Matrix::print(ostream& out) const
{// put the vector into the stream out
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++)
	 out << element[i*cols+j] << "  ";
      out << endl;}
}
//overload <<
ostream& operator<<(ostream& out, const Matrix& x)
{
   x.print(out);
   return out;
}
