/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/

#include "BIC.h"

/* Here is the actual remote procedure */
/* The return value of this procedure must be a pointer to int! */
/* we declare the variable result as static so we can return a 
   pointer to it */

long *
add_1_svc(operands *argp, struct svc_req *rqstp)
{
   static long result;
   
   printf("Got request: adding %d, %d\n",
	  argp->x, argp->y);
   
   result = argp->x + argp->y;
   
   return(&result);
}

long *
sub_1_svc(operands *argp, struct svc_req *rqstp)
{
   static long result;
   
   printf("Got request: subtracting %d, %d\n",
	  argp->x, argp->y);
   
   result = argp->x - argp->y;
   
   return(&result);
}

long *
multi_1_svc(operands *argp, struct svc_req *rqstp)
{
   static long result;

   printf("Got request: multiplication %d, %d\n",
	  argp->x, argp->y);

   result = argp->x * argp->y;

   return(&result);
}

long *
div_1_svc(operands *argp, struct svc_req *rqstp)
{
   static long result;

   printf("Got request: division %d, %d\n",
	  argp->x, argp->y);

   result = argp->x / argp->y;

   return(&result);
   
}
