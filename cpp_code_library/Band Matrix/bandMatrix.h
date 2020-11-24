#ifndef BANDMATRIX_H
#define BANDMATRIX_H
#include <iostream>
#include <ostream>
using namespace std;

class bandMatrix {
  public:
   bandMatrix(int dim = 0, int ubw = 0, int lbw = 0);
   bandMatrix(const bandMatrix& m); //copy constructor
   ~bandMatrix();
   void fill();
   double operator()(int i, int j) const; //element access
   bandMatrix& operator=(const bandMatrix& m);
   bandMatrix operator+() const; //unary plus
   bandMatrix operator+(const bandMatrix& m) const;
   bandMatrix operator-() const; //unary minus
   bandMatrix operator-(const bandMatrix& m) const;
   bandMatrix operator*(const bandMatrix& m) const;
   bandMatrix& operator+=(const double& x);
   void print(ostream& out) const;
   double getNum(int = 0, int  = 0) const;
  private:
   int rows, uppbw, lowbw, lowsize, uppsize, size; //rows will be used for both
                                                   //rows and cols
   double *element; //array
};
ostream& operator<<(ostream& out, const bandMatrix& x);

//Element Mapping Function: getNum
/*
  The function first checks the entries within the main band of the matrix.
  We know that the first element of the main band comes after the entries for
  the lower band, so we move past those and then increment into the main band.
  In the next statements we check to see if the entry is in the upper or lower
  bands. For the lower band, we start at the first entry of the main band and
  work backward. This means that we start at the bottom row and work our way up.
  We take the difference between i and j and move up the rows until we are at
  that point. Adding j takes us to the entry.
  We do something similar for the upper band. We start by passing the lower and
  main bands, and then moving up by i to take us past the entry we are looking
  for. Again, after this we need to move back by the row the entry is in.
  We also check for values (0's) that we have not stored and output them in the
  places they would normally be.
  
  
 */
#endif
