void quicksort(int A[], int start, int end)
{
   if (end - start > 1)
   {
      int pivot = partition(A, start, end);
      quicksort(A,start,pivot);
      quicksort(A,pivot+1,end);
   }
}

int partition(int A[], int start, int end)
{
   int pivPos = start; //the pivot element is the first element
   int i = start+1;
   for (int j = start+1; j < end; j++)
      if (A[j] < A[pivPos])
	 swap(A[i++], A[j]);
   swap (A[pivPos],A[i-1]);
   return i-1;
}