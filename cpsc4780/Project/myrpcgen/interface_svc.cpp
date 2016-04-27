#include "interface.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define testDefine1 testDefine1Value
#define testDefine2 testDefine2Value
#define thisIsTheNameOfTheProgram 55555

static void
thisIsTheNameOfTheProgram_1(struct my_svc_req *rqstp, myrpcsvc *transp)
{
void* result;
void (*_xdr_argument) (void* typ , void* str);
void (*_xdr_result) (void* typ , void* str);
void *(*local)(void *, struct my_svc_req *);
caddr_t argument;

switch (rqstp->my_rq_proc) {

case ADD:
_xdr_argument = &my_xdr_int;
_xdr_result = &my_xdr_int;
local = (void *(*)(void *, struct my_svc_req *))add_1_svc;
break;

case SUB:
_xdr_argument = &my_xdr_float;
_xdr_result = &my_xdr_float;
local = (void *(*)(void *, struct my_svc_req *))sub_1_svc;
break;

case CADD:
_xdr_argument = &my_xdr_char;
_xdr_result = &my_xdr_char;
local = (void *(*)(void *, struct my_svc_req *))cadd_1_svc;
break;

default:
cout << " Error in interface definition. " << endl;
}
my_svc_getargs (transp, _xdr_argument, argument);
result = (*local)((void *)argument, rqstp);
my_svc_sendreply(transp, _xdr_result, (char*)result);
return;
}

int main(int argc, char **argv)
{
myrpcsvc* transp;
if (!my_svc_register(transp, thisIsTheNameOfTheProgram, 1, thisIsTheNameOfTheProgram_1 )) {
std::cout << "Error: unable to register: thisIsTheNameOfTheProgram, 55555 " << std::endl;
exit(1);
}

my_svcudp_create();
my_svc_run();
std::cout << " Error: svc_ren returned. " << std::endl;
return 0; // should never be reached
}

