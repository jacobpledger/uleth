//******************************************************************************
//Written by: Jacob Pledger
//Purpose:To output a numerical diamond pattern
//******************************************************************************

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   int len = 1;
   int c;
   int col; //use this as a counter to increment rows
   int wid;
   int x = 1; //row counter
   int n;

//get user input
   
   cout << "column: ";
   cin >> col;
   
   cout << "width: ";
   cin >> wid;

//error messages
   
   if ((col + wid) >= 75 && (col - wid) <= 0)
      cout << "Diamond hits both sides" << endl;
   
   else if ((wid + col) >= 75)
      cout << "Diamond hits right side" << endl;
   
   else if ((col - wid) <= 0)
      cout << "Diamond hits left side" << endl;
   else
   {
   
//create columns
   
   for (n=1; n <= 7; n++)
      cout << setw(10) << n;
   
   cout << endl;
   
   while (len <=75)
   {
      cout << (len % 10);
      len++;
   }

   cout << endl;
      
//create diamond
      
//for top half
      
      while (x <= wid)
      { 
	 cout << setw(col-x) << " ";

         //for upper left
	 
	 for (c = x; c >=2; c--)
	    cout << (c % 10);
	 
	 //for upper right
	 
	 for (c = 1; c <= x; c++)
	    cout << (c % 10);
	 
	 cout << endl;
	 
	 x++;
      }

//for bottom half
      
      x = (wid-1);
      
      while (x >= 1)
      {
	 cout << setw(col-x) << " ";

	 //for lower left
	 
	 for (c = x; c >=2; c--)
	    cout << (c % 10);
	 
	 //for lower right
	 
	 for (c = 1; c <= x; c++)
	    cout << (c % 10);
	 
	 cout << endl;
	 
	 x--;
      }
   }
   cout << endl;
   
   
   return 0;
}
