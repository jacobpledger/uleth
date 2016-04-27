#include <iostream>
#include "interface.h"
#include "myrpcsvc.h"
#include "myrpc.h"
#include "myxdr.h"
#include "myrpcstructs.h"

int *
add_1_svc(void *argp, struct my_svc_req *rqstp)
{
	static int result;
	
	int *argint = (int *) argp;
	
	std::cout << "Got request: adding " << std::endl;
	
	result = *argint + 1;
	
	return(&result);
}

float *
sub_1_svc(void *argp, struct my_svc_req *rqstp)
{
	static float result;
	
	float *argfloat;
	argfloat = (float*) argp;
	
	std::cout << "Got request: subtracting " << std::endl;
	
	result = *argfloat - 1.01;
	
	return(&result);
}

char *
cadd_1_svc(void *argp, struct my_svc_req *rqstp)
{
	static char* result;
	
	char *c = (char *) argp;
	
	std::cout << "Got request: adding " << std::endl;
	
	
	result = "cat";
	
	
	
	return(result);
}
