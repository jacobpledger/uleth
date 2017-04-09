#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class Matrix {
  public:
   explicit Matrix(int r = 0, int c = 0);
   Matrix(const Matrix& m); //copy constructor
   ~Matrix() {delete [] element;}
   double& operator()(int i, int j) const;
   Matrix& operator=(const Matrix& m);
   Matrix operator+() const; //unary +
   Matrix operator+(const Matrix& m) const;
   Matrix operator-() const; //unary minus
   Matrix operator-(const Matrix& m) const;
   Matrix operator*(const Matrix& m) const;
   Matrix& operator+=(const double& x);
   void print(ostream& out) const;
  private:
   int rows, cols;
   double *element; //array
};
ostream& operator<<(ostream& out, const Matrix& x);
#endif

