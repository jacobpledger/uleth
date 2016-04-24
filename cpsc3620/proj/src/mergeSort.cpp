void mergeSort(vector<point> points)
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

void merge(vector<point> B,vector<point> C,vector<point> A)
{
  int i=0; //for indexing B
  int j=0; //for indexing C
  int k=0; //for indexing A
  while(i < B.size() && j < C.size())
    {
      if(B[i].x <= C[j].x)
	{
	  A[k] = B[i];
	  ++i; ++k;
	}
      else
	{
	  A[k] = C[j];
	  ++j; ++k;
	}
      if(i == B.size()) //C is not finished yet
	while(j <= C.size())
	  A[k] = C[j];
      else if (j == C.size()) //B is not finished yet
	while(i <= B.size())
	  A[k] = B[i];
    }
}
