#include "myrpc.h"
#include <string>
using namespace std;

myrpcsvc *trns;
void (*my_svc_fun) (struct my_svc_req *rqstp, myrpcsvc *transp);
char* in_data;
int PROG;
int VERSION;

//// SERVER STUB

// corresponding to svcudp_create()
// sets up socket to be used in svc_run()
void my_svcudp_create()
{
    //Use lookup function on myport mapper to determine port assigned
    cout << "creating registrar...";
	myrpcsvc* registrar = new myrpcsvc();
	registrar->create();
	cout << "done\n";
	cout << "connecting registrar...";
    registrar->connect("localhost", 10111);
	cout << "done\n";
    string p = my_xdr_int(PROG);
	cout << "sending lookup...";
    registrar->send("lookup;" + p + "; ; ");
	cout << "done\n";
    
    string service;
	cout << "Receiving response...";
    /*if ( !registrar->receive(service) ) {
		cout << "my_svcudp_create failed\n";
        exit(2);
    }
	*/
	cout << "Done\n";
    
    /*
    //parse out port address from recevied string
	cout << "parsing service string for port number...";
    int first = service.find(";");
    int second = service.find(";",first + 1);
    int third = service.find(";", second + 1);
    string port = service.substr(second + 1,third);*/
    int portnum = 10112; //my_xdr_int( port.c_str() );
	cout << "done\n";
    
    //Setup socket details internally in preperation for svc_run
	cout << "setting port...";
    trns->setport(portnum);
	cout << "set\n";
	cout << "creating trns...";
    trns->create();
	cout << "done\n";
	cout << "binding socket...";
    trns->bindsocket();
	cout << "done\n";
}

// corresponding to svc_register() but there is no server version // information
// sets up internal data structures for service connections and registers service with my port mapper
bool my_svc_register(myrpcsvc *trnprt,  const int prog, const int version, void (*mysvcfun) (struct my_svc_req *rqstp, myrpcsvc *transp))
{
    //Initialize and set local variables
    trnprt = new myrpcsvc();
	
    trns = trnprt;
    my_svc_fun = mysvcfun;
	
    PROG = prog;
    VERSION = version;
	
    //Register with my port mapper
    myrpcsvc* registrar = new myrpcsvc();
	cout << "creating registrar...";
	registrar->create();
	cout << "done\n";
	cout << "getting registrar IP...";
    char* ipaddress = "127.0.0.1"; //Did not work registrar->getip();
	cout << "done\n";
	cout << "connecting to portmapper...";
    registrar->connect("localhost",10111);
	cout << "done\n";
    string p = my_xdr_int(PROG); //this segfaults
	cout << "prog number is " ;
	cout << p;
	cout << "sending service for registration...";
    registrar->send("register;" + p + ";_;" + ipaddress);
	cout << "done\n";
	//string register_result;
	
	//registrar->receive(register_result);
	
	
	
	
    return true;
}

// corresponding to svc_run()
// listens for connections to service then executes appropriate command
// when connection received
void my_svc_run()
{
	cout << "listening...";
    //listen on socket
    trns->listen();
	cout << "done\n";
    
    while(true)
    {
        myrpcsvc in_sock;
        myrpcsvc out_sock;
        
		cout << "connecting in_sock...";
        trns->accept(in_sock);
		cout << "done\n";
		/*cout << "connecting out_sock...";
        trns->accept(out_sock);
		cout << "done\n";*/
        
        string request;
        
        //receive data from socket.
		cout << "receiving data from socket...";
        in_sock.receive(request);
		cout << "done\n";
        
		cout << "request data " << request << endl;
        //process string received from socket
		cout << "processing service string...";
        string funid, parameter;
        int div = request.find(";");
        funid = request.substr(0, div);
        parameter = request.substr(div+1, request.length());
        cout << " " << parameter << " done\n";
		
        //save request;
		cout << "saving request...\n";
        struct my_svc_req * req;
		cout << "function id " << funid << endl;
        req->my_rq_proc = my_xdr_int(funid.c_str());
		cout << "function id in structure " << req->my_rq_proc<< endl;
        cout << "done\n";
        
        //save parameter data
		cout << "saving parameter data...";
        char * writable = new char[parameter.size() + 1];
        std::copy(parameter.begin(), parameter.end(), writable);
        writable[parameter.size()] = '\0'; 
        in_data = writable;
        delete[] writable;
		cout << "done\n";
        
        //Process request id and run server side code associated
        my_svc_fun(req, &in_sock);
		cout << "ran service fun";
    }
    
}

// corresponding to svc_getargs()
// get argument data stored in rpc and convert to type using xdr function
bool my_svc_getargs(myrpcsvc *transp, void (*xdr) (void* typ , void* str), const caddr_t argument)
{
    xdr(argument, in_data);
    return true;
}

// corresponding to svc_sendreply()
// take address pointed to by result, convert to type using xdr fucntion supplied
// send message through out socket
bool my_svc_sendreply( myrpcsvc *trnprt, void (*xdr) (void* typ , void* str), const caddr_t result )
{
	cout << "composing reply...";
    char* out_message;
    xdr(result, out_message);
    string b = out_message;
	cout << "done\n";
	cout << "sending reply...";
    trnprt->send(b);
	cout << "done\n";
    return true;
}


//// CLIENT STUB

// corresponding to clnt_create() but there is no server ip address 
// information. Remember we are implementing location transparent RPC. 
client* my_clnt_create(char* host, int prog_num, int ver_num)
{
	cout << "declaring client variable...\n";
    client *new_client = new client;
	cout << "initializing prognum with: " << prog_num << endl;;
    new_client->prognum = prog_num;
	cout << "initializing ver_num\n";
    new_client->vernum = ver_num;
    
    //Use lookup function on myport mapper to determine port assigned
    myrpcsvc *registrar = new myrpcsvc();
	cout << "connecting to portmapper...\n";
	registrar->create();

    registrar->connect("localhost", 10111);
	cout << "complete\n";
    string p = my_xdr_int(prog_num);

	cout << "looking up service...\n";
    registrar->send("lookup;" + p + "; ; ");
    
    string service;
	cout << "receiving service...\n";
	
    //registrar->receive(service);
	cout << "complete\n\n";
    
    //parse out port address, ipaddress from recevied string
    //format is command;name;port;ip
	/*
	cout << "parsing service\n";
    int first = service.find(";");
    int second = service.find(";",first + 1);
    int third = service.find(";", second + 1);
    string port = service.substr(second + 1,third);
	*/
    //new_client->port = my_xdr_int(port.c_str());
    new_client->port = 10112;
	/*
    string b = service.substr(third+1, service.length());
    char * writable = new char[b.size() + 1];
    std::copy(b.begin(), b.end(), writable);
    writable[b.size()] = '\0'; 
	*/
    
    //new_client->host = writable;
	new_client->host = "127.0.0.1";
    
    //delete[] writable;
    
    return new_client;
}


// corresponding to clnt_call()
void* my_clnt_call(client *myclient, const int fun_id, void (*paramtype) (void* typ , void* str),
                   const caddr_t parameter, void (*resulttype) (void* typ , void* str), caddr_t result)
{
    myrpcsvc * svc_call = new myrpcsvc();
	svc_call->create();
	cout << "connecting to service..." << endl;
    svc_call->connect(myclient->host, myclient->port);
    cout << "complete" << endl;
	
    //convert and send parameter
    char* paramstr;
    paramtype(parameter, paramstr);
    string send_data = "1;1";//Hard coded in an effort to fix issues.
	
	cout << "data sent " << send_data << endl;
    svc_call->send(send_data);
    
	
    //receive result
    string resultstr;
	
	cout << "receiving result..." << endl;
    svc_call->receive(resultstr);
	cout << "complete" << endl;
    
    //convert result string and save to result to return it.
    void * r = &resultstr;
    resulttype(result,r);
    
    return result;
    
}
