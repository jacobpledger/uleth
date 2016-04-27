#include <stdio.h>
#include <iostream>
#include <string>
#include "interface.h"
//#include "myrpcsvc.cpp"

int add( client *clnt, int x)
{
	int *result;
	int a=x;
	
	/* Call the client stub created by rpcgen */
	result = add_1(&a,clnt);
	if (result==NULL)
	{
        std::cout << "Trouble calling remote procedure: add" << std::endl;
        exit(1);
	}
	
	return(*result);
}

float sub( client *clnt, float x)
{
	float *result;
	float a=x;
	
	/* Call the client stub created by rpcgen */
	result = sub_1(&a,clnt);
	if (result==NULL)
	{
		std::cout << "Trouble calling remote procedure: subtract " << std::endl;
		exit(1);
	}
	
	return(*result);
}

char cadd( client *clnt, char x)
{
	char *result;
	char c=x;
	
	/* Call the client stub created by rpcgen */
	result = cadd_1(&c,clnt);
	if (result==NULL)
	{
		std::cout << "Trouble calling remote procedure: cadd " << std::endl;
		exit(1);
	}
	
	return(*result);
}

int main( int argc, char* argv[] ) 
{
	client *clnt;
	
	int i;
	float f;
	char c;
	
    std::cout << "Please enter an int, a float, and a char:";
	std::cin >> i >> f >> c;
	cout << "You entered: " << i << " " << f << " " << c << endl;
	
    std::string lh = "localhost";
    char * localhost = new char[lh.size() + 1];
    std::copy(lh.begin(), lh.end(), localhost);
    localhost[lh.size()] = '\0'; 
    
	cout << "creating client... \n";
	clnt = my_clnt_create(localhost, thisIsTheNameOfTheProgram, 1);
	cout << "client created \n";
    delete[] localhost;
	
	printf("%d + 1 = %d\n", i, add(clnt,i));
	printf("%f - 1.01 = %f\n", f, sub(clnt,f));
	printf("%c + 1 = %c\n", c, cadd(clnt,c));
	
	return(0);
}
