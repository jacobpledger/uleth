#ifndef MYRPC_H
#define	MYRPC_H

#include "myrpcsvc.h"
#include "myrpcstructs.h"
#include "interface.h"
#include "myrpcsvc.h"
#include "myxdr.h"
#include "myrpcstructs.h"

//// SERVER STUB

// corresponding to svcudp_create()
// sets up socket to be used in svc_run()
void my_svcudp_create();

// corresponding to svc_register() but there is no server version // information
// sets up internal data structures for service connections and registers service with my port mapper
bool my_svc_register(myrpcsvc *trnprt,  const int prog, const int version, void (*mysvcfun) (struct my_svc_req *rqstp, myrpcsvc *transp));

// corresponding to svc_run()
// listens for connections to service then executes appropriate command
// when connection received
void my_svc_run();

// corresponding to svc_getargs()
// get argument data stored in rpc and convert to type using xdr function
bool my_svc_getargs(myrpcsvc *transp, void (*xdr) (void* typ , void* str), const caddr_t argument);

// corresponding to svc_sendreply()
// take address pointed to by result, convert to type using xdr fucntion supplied
// send message through out socket
bool my_svc_sendreply( myrpcsvc *trnprt, void (*xdr) (void* typ , void* str), const caddr_t result );


//// CLIENT STUB

// corresponding to clnt_create() but there is no server ip address 
// information. Remember we are implementing location transparent RPC. 
client* my_clnt_create(char* host, int prog_num, int ver_num);


// corresponding to clnt_call()
void* my_clnt_call(client *myclient, const int fun_id, void (*paramtype) (void* typ , void* str),
                   const caddr_t parameter, void (*resulttype) (void* typ , void* str), caddr_t result);

#endif
