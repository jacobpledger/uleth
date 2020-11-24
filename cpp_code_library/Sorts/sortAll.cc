//***************************************************************************
// CPSC2620 - Spring 2009 - Professor: Dr. S Hossain
// Assignment #3
// This file contains the code that you will need to adapt in order to fulfill
// the requirements of the first part of Assignment #3.  Not all the code
// is needed for this assignment
//***************************************************************************

#include<iostream>
#include<fstream>
#include<cstdlib>            // for atoi
#include<string>
#include<iomanip>
#include"ctimer.h"
#include"rando.h"
#include<vector>

using namespace std;

//
//
// TimeSort(vector<Type> & a, int n) -- time the sort, 
//              parameters are vector and number of elements in vector
//              vector is sorted, output is generated giving stats on sort
//


template <class Type>
void Swap(vector<Type> & v,int j, int k);

// functions for Insertion Sort
template <class Type>
void Insert(vector<Type> & a ,int left,int right);
template <class Type>
void InsertSort(vector<Type> & a, int size);

// Selection sort
template <class Type>
void SelectSort(vector<Type> & a, int size);

// Bubble sort
template <class Type>
void BubbleSort(vector<Type> & a, int n);

// functions for MergeSort
template <class Type>
void Merge(vector<Type> & a, int left,int mid,int right);
template <class Type>
void DoMerge(vector<Type> & a, int left,int right);
template <class Type>
void MergeSort(vector<Type> & a,int n);

// functions for QuickSort
template <class Type>
int Median(vector<Type> & a,int first,int last);
template <class Type>
int Pivot(vector<Type> & a,int first,int last);
template <class Type>
void Quick(vector<Type> & a,int first,int last);
template <class Type>
void QuickSort(vector<Type> & a, int size);

// helper functions
template <class Type>
void print(const vector<Type> &);

template <class Type>
void loadVectorFromFile(vector<Type>&);

   
const  int MAX =  100001; //largest number of array elements
const int CUTOFF = 20; //used in quick/merge sorts

const int MIN_STR = 10; //minimum random string size
const int MAX_STR = 15; //maximum random string size

typedef int INT; // sort this kind of "number"

double NUM = 0; //counter for comparisons

int main()
{
   vector<int>v;
   loadVectorFromFile(v);
   int n = v.size();
   CTimer clock;
   clock.Start();
   //uncomment these as needed:
   
   //InsertSort(v,n);
   //SelectSort(v,n);
   //BubbleSort(v,n);
   //MergeSort(v,n);
   QuickSort(v,n);
   clock.Stop();
   cout << NUM << endl;
   cout << clock.ElapsedTime() << endl;
}

template <class Type>			  
void loadVectorFromFile(vector<Type>& v)
{
   ifstream ins;
   string fileName;
   cout << "What file to open? ";
   cin >> fileName;
   ins.open(fileName.c_str());
   Type value;
   ins >> value;
   while(!ins.eof())
   {
      v.push_back(value);
      ins >> value;
   }
}

template <class Type>
void Swap(vector<Type> & v,int j, int k)
// precondition:  v[j] references value A, v[k] references value B 
// postcondition: v[k] references value B, v[k] references value A 
{
    Type temp = v[j];
    v[j] = v[k];
    v[k] = temp;
}

//*****************************************************

template <class Type>
void Insert(vector<Type> & a ,int left,int right)
// precondition: left <= right
// postcondition: a[left] <= ... <= a[right]
//     
// standard insertion sort between left/right
// for use in small quick/merge cases as well
{
    int k,loc;
    Type hold;
    NUM = NUM+1; //for assignment of k
    for(k=left+1;k<=right;k++) 
    {
       NUM++;
        // shift elements to make room for a[k]
        
        hold = a[k];   // insert this element
        loc = k;       // location for insertion
	NUM = NUM+2;
        while (left < loc  && hold < a[loc-1])
        {
            a[loc] = a[loc-1];
            loc--;
	    NUM = NUM+3;
        }
        a[loc] = hold; NUM++;
    }
}

template <class Type>
void InsertSort(vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted
//
// uses insertion sort     
{
    Insert(a,0,size-1);
}

template <class Type>
void SelectSort(vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted
//     
// standard selection sort
{
    int j,k,min;
    NUM = NUM+1; //for assignment of j
    for(j=0; j< size-1;j++)
    {
       NUM++;
       min = j; NUM = NUM+2;
        for(k=j+1; k<size; k++)
        {
	   NUM++;
            if (a[k] < a[min])
            {
	       min = k; NUM = NUM+2;
            }
        }
        Swap(a,min,j); NUM = NUM+3;
    }
}

template <class Type>
void BubbleSort(vector<Type> & a, int n)
// precondition: n = # of elements in a
// postcondition: a is sorted
//                note: this is a dog of a sort     
{
   NUM++;
   for(int j=n-1; j>0; j--)
   {
      NUM = NUM+2;
      // find largest element in 0..k, move to a[j]
      for(int k=0; k<j; k++)
	 if (a[k+1] < a[k])
	    Swap(a,k,k+1); NUM = NUM+4;
   }
}


template <class Type>
void Merge(vector<Type> & a, int left,int mid,int right)
// precondition: a sorted from a[left] ... a[mid] and from
//               a[mid+1] to a[right]
//               extra storage passed in
// postcondition: a sorted from a[left] ... a[right]     
{
    static vector<Type> b(MAX);           // aux storage
    int lk=left;                          // a's left index 
    int rk = mid+1;                       // a's right index 
    int bk = left;                        // b's index
    NUM = NUM+3;

    while (lk <= mid && rk <= right)      // both parts non-empty?
    {
       NUM+2;
       if (a[lk] <= a[rk])
	  b[bk++] = a[lk++];
       else
	  b[bk++] = a[rk++];
       NUM = NUM+2;
    }
        // finish any leftovers in a (only one of loops below executes)
    
    while (lk <= mid)  b[bk++] = a[lk++]; NUM=NUM+2;
    while(rk <= right) b[bk++] = a[rk++]; NUM = NUM+2;
    
        // copy b back to a
    NUM = NUM+2;
    for(lk=left,rk=left;lk<=right;lk++)
       a[lk] = b[rk++]; NUM = NUM+2;
}

template <class Type>
void DoMerge(vector<Type> & a, int left,int right)
// postcondition: a[left] <= ... <= a[right]     
{
   int mid = (left+right)/2; NUM++;
   NUM++;
    if (right - left > CUTOFF)
    {
        DoMerge(a,left,mid);
        DoMerge(a,mid+1,right);
        Merge(a,left,mid,right);
    }
    else
    {
        Insert(a,left,right);
    }
}

template <class Type>
void MergeSort(vector<Type> & a,int n)
{
    DoMerge(a,0,n-1);
}

template <class Type>
int Median(vector<Type> & a,int first,int last)
// postcondition: returns index of median element of
//            a[first],a[last],a[mid], mid = (first+last)/2
{
    int mid=(first+last)/2;

    if (a[mid] > a[first])
    {
       if (a[last] > a[mid])
       {
	  NUM++;
	  return mid;
       }
       else if (a[last] > a[first])
       {
	  NUM++;
	  return last;
       }
       else
	  return first;
    }
    else
    {
       if (a[last] > a[first])
       {
	  NUM++;
	  return first;
       }
       else if (a[mid] > a[last])
       {
	  NUM++;
	  return mid;
       }
       else
	  return last;
    }
}

template <class Type>
int Pivot(vector<Type>& a, int first, int last)
// postcondition: returns piv such that
//                first <= k <= piv, a[k] <= a[piv]
//                piv < k <= last, a[piv] < a[k]                
// standard Bently/ola pivot routine
{
   int p = first; NUM++;
   Type piv;
   
   //piv = a[first]; NUM++;// selects first element as the pivot
   // if you want the pivot to be the median of the first, middle, and
   // last element you will need to call the above Median function
   // you can also choose a randomly chosen element as the pivot.

   //median pivot
   //piv = a[Median(a,first,last)];

   //random pivot
   RandGen r;
   piv = a[r.RandInt(first,last)];
   
    
   NUM++;
   for(int k=first+1; k<=last; k++)
   {
      NUM = NUM+2;
      if (a[k] <= piv)
      {
	 p++;            
	 Swap(a,k,p); NUM = NUM+3;
      }
   }
   Swap(a,p,first); NUM = NUM+3;
   return p;
}

template <class Type>
void Quick(vector<Type> & a,int first, int last)
// postcondition: a[first] <= ... <= a[list]     
{
    int piv;
    
    if (last - first > CUTOFF)
    {
       piv = Pivot(a,first,last);
       Quick(a,first,piv-1);
       Quick(a,piv+1,last);
       NUM = NUM+2;
    }
    else
    {
        Insert(a,first,last);
    }
}

template <class Type>
void QuickSort(vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted     
{
   Quick(a,0,size - 1);
}

template <class Type>
void print(const vector<Type> & a)
{
   int n = a.size(); NUM = NUM+2;
   for (int i = 1; i <= n; i++)
   {
      cout << setw(15) << a[i-1];
      if(i%(4) == 0)
	 cout << endl;
      NUM = NUM+2;
   }
   cout << endl;
}

