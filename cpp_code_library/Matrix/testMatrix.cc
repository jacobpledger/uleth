// test matrix class

#include <iostream>
#include "matrix.h"
using namespace std;
// test matrix class

#include <iostream>
#include "matrix.h"
using namespace std;
int main()
{
   Matrix X(3,3), Y, Z;
   int i, j;
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
	 X(i,j) = 2*i + j;
   // test indexed access
   cout << "X(2,2) = " << X(2,2) << endl;
   // test overloaded output operator
   cout << "X is" << endl;;
   cout << X << endl;
   // test overloaded assignment operator
   Y = X;
   cout << "Y is" << endl;
   cout << Y << endl;
   X += 2;
   cout << "X incremented by 2 is" << endl;
   cout << X << endl;
   Z = Y + X;
   cout << "Y + X is" << endl;
   cout << Z << endl;
   cout << "-(Y + X) is" << endl;
   cout << -Z << endl;
   Matrix W(3,3);
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
	 W(i,j) = i + j;
   cout << "W is" << endl;
   cout << W << endl;
   Z = Y * W;
   cout << "Y * W is" << endl;
   cout << Z << endl;
   Matrix P(3,1);
   for (i = 0; i < 3; i++)
      for (j = 0; j < 1; j++)
	 P(i,j) = 2*i + j;
   cout << P << endl;
   Z = Z * P;
   cout << Z << endl;

}
