void mergeSort(int p[], int start, int endPos)
{
   int middle;
   if (endPos - start > 0)
   {
      middle = (start + endPos)/2;
      mergeSort(p, start, middle);
      mergeSort(p, middle, start);
      
      merge(p, start, middle, endPos);
   }
}

void merge(int p[], int start, int mid, int end)
{
   int temp[100];
   int j, i1, i2, outi;
   outi = start-1;
   i1 = start;
   i2 = mid+1;
   while (i1 <= mid && i2 <= end)
      if (p[i1] < p[i2])
      {
	 temp[outi] = p[i1];
	 i1++;
      }
      else
      {
	 temp[outi] = p[i2];
	 i2++;
      }
   for (j = i1; i1 <= mid; j++)
   {
      outi++;
      temp[outi] = p[j];
   }
   for (j = start; j < outi; j++)
      p[j] = temp[j];
}
