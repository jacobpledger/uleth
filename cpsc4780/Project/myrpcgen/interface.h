#ifndef _INTERFACE_H_RPCGEN
#define _INTERFACE_H_RPCGEN

#include "myrpc.h"

#define testDefine1 testDefine1Value
#define testDefine2 testDefine2Value
#define thisIsTheNameOfTheProgram 55555

#define ADD 1
extern int * add_1(void *, client *);
extern int * add_1_svc(void *, struct my_svc_req *);
#define SUB 2
extern float * sub_1(void *, client *);
extern float * sub_1_svc(void *, struct my_svc_req *);
#define CADD 3
extern char * cadd_1(void *, client *);
extern char * cadd_1_svc(void *, struct my_svc_req *);

#endif
