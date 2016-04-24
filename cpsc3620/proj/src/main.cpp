#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "point.h"
#include "divideconquer.h"
#include "mergesort.cpp"

using namespace std;

int main()
{
  string n;
  string filename = "output";	//still needs some appending to work
  
  cout << "Please enter a value for n: ";
  cin >> n;
  filename += n;
  filename += ".txt";
  //Should be the correct filename at this point, assuming good user input
  
  ifstream inFile;
  inFile.open(filename.c_str());
  
  //Declare the vector to contain the points from the file
  vector<point> points;
  
  //Read the structs into the vector
  while(!inFile.eof())
    {
      //Grab the points from the file
      point currentPoint;
      inFile >> currentPoint.x >> currentPoint.y;
      
      //Add the points to the vector of all the points
      points.push_back(currentPoint);
    }
  
  mergeSort(points);
  int d = divConq(points);
  
  return 0;
}
