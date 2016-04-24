/* Program to create files containing sets of psedo-random points ranging from -10000 to + 10000
 * Creates 21 different files with the name outputn.txt, where n is the number of points in the file
 *
 * Author: Jeremy Lawson
 * Date: Nov 8, 2010
 */

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

void outputFile(int max, char filename[]);

main()
{
	printf("Creating data points...\n");
	
	//Call the routine for each value of n required
	outputFile(100, "output100.txt");
	outputFile(200, "output200.txt");
	outputFile(300, "output300.txt");
	outputFile(400, "output400.txt");
	outputFile(500, "output500.txt");
	outputFile(600, "output600.txt");
	outputFile(700, "output700.txt");
	outputFile(800, "output800.txt");
	outputFile(900, "output900.txt");
	outputFile(1000, "output1000.txt");
	outputFile(1500, "output1500.txt");
	outputFile(2000, "output2000.txt");
	outputFile(2500, "output2500.txt");
	outputFile(3000, "output3000.txt");
	outputFile(4000, "output4000.txt");
	outputFile(5000, "output5000.txt");
	outputFile(6000, "output6000.txt");
	outputFile(7000, "output7000.txt");
	outputFile(8000, "output8000.txt");
	outputFile(9000, "output9000.txt");
	outputFile(10000, "output10000.txt");
	
}

void outputFile(int max, char filename[])
{
	//Create the file pointer and open file for writing
	FILE *fp;
	fp=fopen(filename, "w");

	int i;
	for(i=0; i<max; i++)
	{
		//random number between -10000 and 10000, including 0
		int num1 = random() % 20001 - 10000;
		int num2 = random() % 20001 - 10000;
		fprintf(fp, "%d %d\n", num1, num2);
	}
}
