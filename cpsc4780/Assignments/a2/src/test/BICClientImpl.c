#include <stdio.h>
#include "BIC.h"

int add( CLIENT *clnt, int x, int y)
{
	operands ops;
	int *result;
	
	/* Gather everything into a single data structure to send to the server */
	ops.x = x;
	ops.y = y;
	
	/* Call the client stub created by rpcgen */
	result = add_1(&ops,clnt);
	if (result==NULL)
	{
		fprintf(stderr,"Trouble calling remote procedure: add\n");
		exit(0);
	}
	
	return(*result);
}

int sub( CLIENT *clnt, int x, int y)
{
	operands ops;
	int *result;
	
	/* Gather everything into a single data structure to send to the server */
	ops.x = x;
	ops.y = y;
	
	/* Call the client stub created by rpcgen */
	result = sub_1(&ops,clnt);
	if (result==NULL)
	{
		fprintf(stderr,"Trouble calling remote procedure: subtract\n");
		exit(0);
	}
	
	return(*result);
}

int mult( CLIENT *clnt, int x, int y)
{
	operands ops;
	int *result;
	
	/* Gather everything into a single data structure to send to the server */
	ops.x = x;
	ops.y = y;
	
	/* Call the client stub created by rpcgen */
	result = mult_1(&ops,clnt);
	if (result==NULL)
	{
		fprintf(stderr,"Trouble calling remote procedure: multiply\n");
		exit(0);
	}
	
	return(*result);
}

int div( CLIENT *clnt, int x, int y)
{
	operands ops;
	int *result;
	
	/* Gather everything into a single data structure to send to the server */
	ops.x = x;
	ops.y = y;
	
	/* Call the client stub created by rpcgen */
	result = div_1(&ops,clnt);
	if (result==NULL)
	{
		fprintf(stderr,"Trouble calling remote procedure: divide\n");
		exit(0);
	}
	
	return(*result);
}

int main( int argc, char *argv[])
{
	CLIENT *clnt;
	
	int x,y;
	if (argc!=4)
	{
		fprintf(stderr,"Usage: %s hostname num1 num\n",argv[0]);
		exit(0);
	}
	
	clnt = clnt_create(argv[1], BIC, BIC_VERSION, "udp");
	
	/* Make sure the create worked */
	if (clnt == (CLIENT *) NULL)
	{
		clnt_pcreateerror(argv[1]);
		exit(1);
	}
	
	/* get the 2 numbers that should be added */
	x = atoi(argv[2]);
	y = atoi(argv[3]);
	
	printf("%d + %d = %d\n", x, y, add(clnt,x,y));
	printf("%d - %d = %d\n", x, y, sub(clnt,x,y));
	printf("%d * %d = %d\n", x, y, mult(clnt,x,y));
	printf("%d / %d = %d\n", x, y, div(clnt,x,y));

	return(0);
}