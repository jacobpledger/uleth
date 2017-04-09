void insertion_sort(int a[], int n)
{
	for (unsigned int i = 1; i < n; i++)
	{
		int e = a[i]
		int j = i;
		while ( ( j > 0) && (a[j-1] > e) )
		{
			a[j] = a[j-1];
			j--;
		}
	}
	a[j] = e;
}