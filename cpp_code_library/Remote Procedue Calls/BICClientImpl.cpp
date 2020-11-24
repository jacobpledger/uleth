

#include <stdio.h>
#include "BIC.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */

long add( CLIENT *clnt, long x, long y) {
  operands ops;
  long *result;

  /* Gather everything into a single data structure to send to the server */
  ops.x = x;
  ops.y = y;

  /* Call the client stub created by rpcgen */
  result = add_1(&ops,clnt);
  if (result==NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }
  return(*result);
}

/* Wrapper function takes care of calling the RPC procedure */

long sub( CLIENT *clnt, long x, long y) {
   operands ops;
   long *result;

   /* Gather everything into a single data structure to send to the server */
   ops.x = x;
   ops.y = y;
   
   /* Call the client stub created by rpcgen */
   result = sub_1(&ops,clnt);
   if (result==NULL) {
      fprintf(stderr,"Trouble calling remote procedure\n");
      exit(0);
   }
   return(*result);
}

long multi( CLIENT *clnt, long x, long y) {
  operands ops;
  long *result;

  /* Gather everything into a single data structure to send to the server */
  ops.x = x;
  ops.y = y;

  /* Call the client stub created by rpcgen */
  result = multi_1(&ops,clnt);
  if (result==NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }
  return(*result);
}

/* Wrapper function takes care of calling the RPC procedure */

long div( CLIENT *clnt, long x, long y) {
   operands ops;
   long *result;

   /* Gather everything into a single data structure to send to the server */
   ops.x = x;
   ops.y = y;
   
   /* Call the client stub created by rpcgen */
   result = div_1(&ops,clnt);
   if (result==NULL) {
      fprintf(stderr,"Trouble calling remote procedure\n");
      exit(0);
   }
   return(*result);
}



int main( int argc, char *argv[]) {
   CLIENT *clnt;
   result *ret;
   
   int x,y;
   if (argc!=4) {
     fprintf(stderr,"Usage: %s hostname num1 num\n",argv[0]);
     exit(0);
   }

   /* Create a CLIENT data structure that reference the RPC
      procedure BIC_PROG, version SIMP_VERSION running on the
      host specified by the 1st command line arg. */

   clnt = clnt_create(argv[1], BIC_PROG, BIC_VERSION, "udp");

   /* Make sure the create worked */
   if (clnt == (CLIENT *) NULL) {
      clnt_pcreateerror(argv[1]);
      exit(1);
   }

   /* get the 2 numbers that should be added */
   x = atoi(argv[2]);
   y = atoi(argv[3]);

   
   printf("%d + %d = %d\n", x, y, add(clnt,x,y));
   printf("%d - %d = %d\n", x, y, sub(clnt,x,y));
   printf("%d + %d = %d\n", x, y, multi(clnt,x,y));
   printf("%d - %d = %d\n", x, y, div(clnt,x,y));


  return(0);
}



