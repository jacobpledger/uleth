//Brute force solution to the closest pair problem
//
//Nov 11, 2010

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

//Struct to hold the individual x-y pairs
struct point{
	int x, y;
};

//Algorithm for brute-forcing the closest pair from a vector of points
//input points: vector containing all the x-y points
void bruteForce(vector<point> points)
{
	double dmin = 29000;	//Points have range -10000 to 10000, this value is guaranteed to be larger than the possible distance of slightly over 28000
	double distance;
	point point1, point2;
	for(int i=0; i<points.size()-1; i++)
	{
		for(int j=i+1; j<points.size(); j++)
		{
			//extract the points
			int x1=points[i].x;
			int y1=points[i].y;
			int x2=points[j].x;
			int y2=points[j].y;
			
			//determine the distance between the points
			distance=sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

			//Check if the new distance is smaller, and that it's not the same point
			if(distance<dmin && distance != 0){
				dmin=distance;
				point1=points[i];
				point2=points[j];
			}
		}
	}
	cout << "The closest points are:\nx: " << point1.x << ", y: " << point1.y << "\nx: " << point2.x << ", y: " << point2.y << endl;
	cout << "The distance between the two points is " << dmin << endl;
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

	// Set up the clock
	clock_t startTime = clock();

	//Call the brute force algorithm to determine the closest point. This function will also report the closet points to the user.
	bruteForce(points);

	//Get the end time
	clock_t endTime = clock();

	cout << "Time taken (seconds): " << ((endTime - startTime) / (double)CLOCKS_PER_SEC) << endl;

	return 0;
}
