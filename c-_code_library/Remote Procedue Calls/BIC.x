/* Protocol definition file for a simple RPC application */

/* This file is the most important file in a RPC application */


/* This simple RPC application has the following remote procedures.

   Two remote procedures - an add procedure and a subtract procedure. 
      Each must be called with a single parameter, a structure 
      that holds two integers. The return value of each procedure is 
      an int.

   Two remote procedures - an add procedure and a subtract procedure.
      Each must be called with a single parameter, a structure
      that holds two integers. The return value 
      of each procedure is another structure, which contains the two 
      integers and the result of the addition or subtraction.

   The purpose of this arrangement is to let you get familiar with
   the parameter passings in RPC procedures. */


/* Notice that we can put our comments in the protocol definition file!
   The format of comments are similar to the one in language C. You
   have seen it already. */

/* We can also put defines in here - and use them, although they will
   not show up in the .h file produced by rpcgen. 
   
   Remember rpcgen will generate *.h file related for a RPC application. */

#define VERSION_NUMBER 1

/* If we want to put something explicitly in the .h file produced by rpcgen
   we can start it with %:

   rpcgen just strips the '%' and puts the rest in the .h file. */

%#define foo 127
%#define Pi 3.1415926


/* The following is the definition of the data type that will be passed to
   and passed out from both of the remote procedures */

/* Note that this data type will be defined in the .h file produced by
   rpcgen. AND it will be typedef'd as well, so we can refer to it as
   type 'operands' and do not need to use 'struct operands'. */

struct operands {
	int x;
	int y;
};

struct result {
        int x;
        int y;
        int r;  /* The result will be put here. */
};

/* OK - here is the real stuff - the program, version and procedure
definitions. Remember this is not C, although it looks similar. */

program SIMP_PROG {
   version SIMP_VERSION {
     int ADD(operands) = 1;      /* Take a struct containing two integers */
                                 /* and return the result of addition. */

     int SUB(operands) = 2;      /* Take a struct containing two integers */
                                 /* and return the result of subtraction. */

     result TWOADD(operands) = 3;/* Take a struct containing two integers */
                                 /* and return a struct containing the two */
                                 /* integers and addition result. */

     result TWOSUB(operands) = 4;/* Take a struct containing two integers */
                                 /* and return a struct containing the two 
                                 /* integers and subtraction result. */
                               
   } = VERSION_NUMBER;
} = 555555555;

/* There are three numbers here. */
/* program number - SIMP_PROG. In the above example, it is 555555555.
                    Within our client and server code, we can just refer to
                    it as SIMP_PROG.
                    In other words, rpcgen will put this line in the .h file:
                    #define SIMP_PROG 555555555 */
		    
/* version number - SIMP_VERSION. In the above example, it is 1. */
/* remote procedure numbers - 1 for procedure ADD
                              2 for procedure SUB
                              3 for procedure TWOADD
                              4 for procedure TWOSUB
                             
                              We can also use the symbolic constants 
                              ADD, SUB, TWOADD, and TWOSUB to refer to
                              them, correspondingly.

/* Use the following command to compile the protocol and generate
   necessary header and stub files for the client and server. */

/* rpcgen -C simp.x */
/* The -C tells rpcgen to output ANSI C code (not K&R).
   the -Sc tells rpcgen to output sample client code that makes a
   call to each of the remote procedures, you can take this
   code and adjust it to your needs. */
   
/* On the client side, a stub will be generated in simp_clnt.c for 
   each of the remote procedures. For example, the stub prototype for 
   the add procedure looks like this:

   int * add_1(operands *, CLIENT *);

   the "add" part of the name comes from the ADD in the protocol
   definition. the "_1" indicates the version number (if we set the
   version to 100, the stub name would be "add_100").

   When we call this procedure in the client, this stub takes care of 
   all the RPC stuff for us, all we have to do is give it the address
   of an operands structure with the x and y fields set, and an 
   RPC handle that is already established (the CLIENT * arg). */

/* On the server side, rpcgen creates the file simp_svc.h that includes
   a main() and an RPC dispatch routine. All we need to supply is the
   actual remote procedure subroutines. 

   The server expects these routines to have prototypes like this:

   int *add_1_svc(operands*, struct svc_req *);
   int *sub_1_svc(operands*, struct svc_req *);
   operands *twoadd_1_svc(operands*, struct svc_req *);
   operands *twosub_1_svc(operands*, struct svc_req *);

   We need to write these routines, and include them in the link used
   to create the server executable. */


