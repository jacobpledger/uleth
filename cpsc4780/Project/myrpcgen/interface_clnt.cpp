#include "interface.h"

int *
add_1(void* args, client *clnt)
{
int* clnt_res;
my_clnt_call( clnt, ADD, &my_xdr_int, (caddr_t) args, &my_xdr_int, (caddr_t) clnt_res );
return clnt_res;
}

float *
sub_1(void* args, client *clnt)
{
float* clnt_res;
my_clnt_call( clnt, SUB, &my_xdr_float, (caddr_t) args, &my_xdr_float, (caddr_t) clnt_res );
return clnt_res;
}

char *
cadd_1(void* args, client *clnt)
{
char* clnt_res;
my_clnt_call( clnt, CADD, &my_xdr_char, (caddr_t) args, &my_xdr_char, (caddr_t) clnt_res );
return clnt_res;
}

