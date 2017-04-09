#include "myrpcsvc.h"

#ifndef SocketException_class
#define SocketException_class

#include <string>

class SocketException
{
 public:
  SocketException ( std::string s ) : m_s ( s ) {};
  ~SocketException (){};

  std::string description() { return m_s; }

 private:

  std::string m_s;

};

#endif

//Constructor
myrpcsvc::myrpcsvc()
{
    this->_port = -1;
    _socket = new Socket();
}

//Destructor
myrpcsvc::~myrpcsvc()
{
    delete _socket;
}

bool myrpcsvc::create()
{
	return _socket->create();
}

//update port to
void myrpcsvc::setport(int port)
{
    if (this->_port == -1)
        this->_port = port;
}

//retreive configured port
int myrpcsvc::getport()
{
    return this->_port;
}

//run socket bind socket
void myrpcsvc::bindsocket()
{
    if (this->_port != -1)
    {
        _socket->bind(_port);
    }
}

bool myrpcsvc::connect (const std::string host, const int port)
{
    _socket->connect(host, port);
    return true;
}

//Start listen
bool myrpcsvc::listen()
{
    return _socket->listen();
}

//
bool myrpcsvc::accept(myrpcsvc& new_socket)
{
    return _socket->accept(new_socket.getSocket());
}

bool myrpcsvc::send(const std::string s)
{
    return _socket->send(s);
}

int myrpcsvc::receive(std::string& s)
{
	try
	{
		return _socket->recv(s);
	}
	catch(SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }
}

char* myrpcsvc::getip()
{
    char* ipaddress;
    _socket->getprimaryip(ipaddress, sizeof(ipaddress));
    return ipaddress;
}

Socket* myrpcsvc::getSocket() 
{
    return _socket;   
}
