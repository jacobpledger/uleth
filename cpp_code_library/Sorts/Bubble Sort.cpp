void bubbleSort(int A[], int size )
{
	bool swapped;

	do
	{
		swapped = false;
		for (unsigned int i = 0; i < size; ++i)
			if (A[i] > A[i+1])
				swapped = swap(A[i], A[i+1]);
		size--;
	}
	while (swapped);
}

bool swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
	return true;
}			