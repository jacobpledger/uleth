#include "myxdr.h"
#include <string>
using namespace std;

// convert int to string
void my_xdr_int(void* i, void* s)
{
	if(i == NULL)
	{
		int outint = my_xdr_int((char *)s);
		i = (void*) &outint;
	}
	else if(s == NULL)
	{
        int a;
        a = * (int *) i;
        string outstring = my_xdr_int(a);
		s = (void*) outstring.c_str();
	}
}

// convert float to string
void my_xdr_float(void* f, void* s)
{
	if(f == NULL)
	{
		float outfloat = my_xdr_float((char*) s);
		f = (void*) &outfloat;
	}
	else if(s == NULL)
	{	
		string outstring = my_xdr_float(*(float*) f);

		
		s = (void*) outstring.c_str();
	}
}

// convert char to string
void my_xdr_char(void* c, void* s)
{
	if(c == NULL)
	{
		c = s;
		
	}
	else if(s == NULL)
	{
		s = c;
	}
}

int my_xdr_int(const char* a)
{
	return atoi(a);
}

string my_xdr_int(int i)
{
	stringstream out;
	out << i;
	return out.str();
}

float my_xdr_float(const char* a)
{
	return atof(a);
}

string my_xdr_float(float f)
{
	stringstream out;
	out << f;
	return out.str();
}

