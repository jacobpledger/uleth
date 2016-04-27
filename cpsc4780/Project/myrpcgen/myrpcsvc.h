#ifndef MYRPCSVC_H
#define	MYRPCSVC_H

#include "Socket.h"

class myrpcsvc {

public:

    myrpcsvc();
    virtual ~myrpcsvc();
    
    void setport(int);
    void bindsocket();
    bool listen();
    bool create();
    bool accept(myrpcsvc& );
    bool send(const std::string );
    int receive(std::string& );
    
    int getport();
    Socket* getSocket();
    
    // Client initialization
    bool connect (const std::string , const int );
    char* getip();

private:
    int _port;
    Socket *_socket;

};

#endif
