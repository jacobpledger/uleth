#include <iostream>
using namespace std;

int findMax(int p[], int end)
{
   int maxIndex = 0;
   for (int i = 1; i <= end; i++)
      if (p[i] > p[maxIndex])
	 maxIndex = i;
   return maxIndex;
}

void selectionSort(int p[], int size)
{
   int max;
   for (int i = 0; i < size-1; i++)
   {
      max = findMax(p, i);
      if (max < i)
	 swap(p[i], p[max]);
   }
}

void swap(int &a, int &b)
{
   int temp = a;
   a = b;
   b = temp;
}