#include "bandMatrix.h"
#include <iostream>
using namespace std;

int main()
{
   bandMatrix M(4,1,1);

   //test input & output
   M.fill();
   cout << M << endl;

   // test mapping functions
   cout << "M(2,2) = " << M(2,2) << endl;
   cout << endl;
   
   // test overloaded assignment operator
   bandMatrix A;
   A = M;
   cout << "A is: " << endl;
   cout << A << endl;
   
   //test arithmetic operations
   M += 2;
   cout << "M incremented by 2 is: " << endl;
   cout << M << endl;

   bandMatrix B;
   B = M + A;
   cout << "M + A is: " << endl;
   cout << B << endl;

   //gives a memory corruption error after, but still outputs somehow (oh well,
   //everything after it doesn't work anyway)
   
   cout << "-(A + M) is: " << endl;
   cout << -B << endl;
   
   //this gives a segmentation fault
   bandMatrix C;
   C = M - A;
   cout << "M - A is: " << endl;
   cout << C << endl;
   
   //this has not been properly implemented
   B = M * A;
   cout << "M * A is: " << endl;
   cout << B << endl;
      
   return 0;
}
