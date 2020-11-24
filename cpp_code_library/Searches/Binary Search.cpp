template <class T>

T BinarySearch(T A[n], T key)
{
	int m;
	int l = 0;
	int r = n-1;
	while (l <= r)
	{
		m=(l+r)/2
		if (key == A[m])
			return m;
		else
			if (key < A[m]
				r= m-1;
			else
				l = m+1;
	}
}