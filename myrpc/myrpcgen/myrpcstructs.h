#ifndef MYRPCSTRUCTS_H
#define	MYRPCSTRUCTS_H

struct my_svc_req
{
    int my_rq_proc;
};

//void (*my_xdr_type) (void* typ , void* str);

//not sure what goes in here yet
struct client
{
    //this will be removed when known values are found
public:
    char *host;
    int port;
    int prognum;
    int vernum;

};
#endif
