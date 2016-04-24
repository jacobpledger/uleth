#include <vector>
#include <iostream>
#include <cmath>
#include "point.h"
#include <fstream>
#include <ctime>

using namespace std;

int abs(int); //forward declaration
void mergeSort(vector<point> &points);
void merge(vector<point> &B,vector<point> &C,vector<point> &A);

//input points: vector containing all the x-y points
double divConq(vector<point> points)
{
  double d; //smallest distance between 2 points
  
  //if we only have one point, we can't calculate distance...
  //...return impossibly large number (max point range is around 28k
  if(points.size() == 1)
    d = 29000;
  
  //if there are exactly 2 points, calculate the distance between them
  if(points.size() == 2)
    {
      int xdif = points[1].x - points[0].x;
      int ydif = points[1].y - points[0].y;
      d = sqrt((xdif*xdif)+(ydif*ydif));
    }
  
  //if the number of points are > 2, we can divide this problem
  else if(points.size() > 2)
    {
      int midLine = points.size()/2; //line to divide points in half
      
      int lh = midLine - 1; //end deliniator left half
      int rh = points.size(); //end deliniator for right half
      int i = 0; //for iterating right half
      int j = midLine; //for iterating left half
      vector<point>leftHalf;
      vector<point>rightHalf;
      
      //create the left & right halves...
      while(i <= lh && j <= rh)
	{
	  leftHalf.push_back(points[i]);
	  rightHalf.push_back(points[j]);
	  i++;
	  j++;
	}
      
      //...and find the smallest distance in them
      double d1 = divConq(leftHalf);
      double d2 = divConq(rightHalf);
      if (d1 < d2 && d1 < d)
	d = d1;
      else if (d2 < d)
	d = d2;
      
      //Scan through all the points on the left side within d of mid on x co-ord
      //For each of these, compare with points on right side within d x or y
      //For any points that exists, compare distance & check if it's a new minimum
      
      int leftHalfEnd = leftHalf.size() -1;
      //Calculate the midpoint y=c
      double c = (rightHalf[0].x - leftHalf[leftHalfEnd].x) / 2;
      
      //Get the points in the left half within d of the mid line
      for(int i=leftHalfEnd; i>=0 && (abs(c - leftHalf[i].x) <=d); i--)
	{
	  //Compare points within d of the point. Will be at most 6 points to compare.
	  for(int j=0; j<6 && j<rightHalf.size(); j++)
	    {
	      int xDif = abs(rightHalf[j].x - c);
	      int yDif = abs(rightHalf[j].y - c);
	      if(xDif <=d && yDif <= d)
		{
		  double dPrime;
		  int xdifPrime = leftHalf[i].x - rightHalf[j].x;
		  int ydifPrime = leftHalf[i].y - rightHalf[j].y;
		  dPrime = sqrt ((xdifPrime * xdifPrime) + (ydifPrime * ydifPrime));
		  if(dPrime < d && dPrime != 0)
		    d = dPrime;
		}
	    }
	}
      
      
    }
  
  return d;
}

int abs(int num)
{
  if(num > 0)
    return num;
  else if(num < 0)
    return num*-1;
}

int main()
{
  string n;
	string filename = "output";	//still needs some appending to work

	cout << "Please enter a value for n: ";
	cin >> n;
	filename += n;
	filename += ".txt";		//Should be the correct filename at this point, assuming good user input

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
	
	//Set up the clock
	clock_t startTime = clock();

	mergeSort(points);
		
	for(int c = 0; c < points.size(); c++)
	  cout << points[c].x << ',' << points[c].y << endl;
	
	double min;
	min = divConq(points);
	
	//Get the end value for the time
	clock_t endTime = clock();

	cout << "Minimum distance: " << min << endl;
	cout << "Time taken (seconds): " << ((endTime - startTime) / (double)CLOCKS_PER_SEC) << endl;


	return 0;
}

void mergeSort(vector<point> &points)
{
  if (points.size() > 1)
    {
      int limitB = (points.size()/2) - 1;
      int limitC = points.size();
      int i = 0;
      int j = points.size()/2;
      vector<point>B;
      vector<point>C;
      while(i <= limitB && j <= limitC)
	{
	  B.push_back(points[i]);
	  C.push_back(points[j]);
	  i++;
	  j++;
	}
      
      mergeSort(B);
      mergeSort(C);
      merge(B,C,points);
    }
}

void merge(vector<point> &B,vector<point> &C,vector<point> &A)
{
  int i=0; //for indexing B
  int j=0; //for indexing C
  int k=0; //for indexing A

  while(i < B.size() && j < C.size())
    {
      if(B[i].x <= C[j].x)
	{
	  A[k].x = B[i].x;
	  A[k].y = B[i].y;
	  ++i; ++k;
	}
      else
	{
	  A[k].x = C[j].x;
	  A[k].y = C[j].y;
	  ++j; ++k;
	}
      if(i == B.size()) //C is not finished yet
	while(j <= C.size())
      	{
	  A[k].x = C[j].x;
	  A[k].y = C[j].y;
	  ++j, ++k;
	}
      else if (j == C.size()) //B is not finished yet
	while(i <= B.size())
	{
	  A[k].x = B[i].x;
	  A[k].y = B[i].y;
	  ++i, ++k;
	}
    }
}
