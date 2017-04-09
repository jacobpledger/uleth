#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    try 
    {
        ClientSocket out_socket("myhost", 30000);
        ClientSocket in_socket("myhost", 30000);
        std::string data;

        try
        {
            while (true)
            {
                for (int i = 1; i <= 10; i++)
                {
                    in_socket >> data;

                    if ( (i == 9) && (rand() % 2 == 0) )
                    {
                        out_socket << "NAK";
                        //std::cout << "[*NAK*]"; //Test line
                    }
                    else
                    {
                        out_socket << "ACK";
                        std::cout << data;
                    }
                }
            }
        }
        catch(SocketException&)
        {
        }
	std::cout << "\n";
    }
    catch(SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}
