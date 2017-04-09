#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
using std::ifstream;
using std::istream;
using std::string;
using std::stringstream;
using namespace std;
pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

void *readNwrite(void *out);
string getString(int numChars, ifstream &is);

main()
{
     pthread_t thread1, thread2, thread3, thread4, thread5;
     char *m1 = "read1", *m2 = "read2", *m3 = "read3", *m4 = "read4", *m5 = "read5";

     pthread_create( &thread1, NULL, readNwrite, (void*) m1);
     pthread_create( &thread2, NULL, readNwrite, (void*) m2);
     pthread_create( &thread3, NULL, readNwrite, (void*) m3);
     pthread_create( &thread4, NULL, readNwrite, (void*) m4);
     pthread_create( &thread5, NULL, readNwrite, (void*) m5);


     pthread_join(thread1,NULL);
     pthread_join(thread2,NULL);
     pthread_join(thread3,NULL);
     pthread_join(thread4,NULL);
     pthread_join(thread5,NULL);


     return 0;
}


void *readNwrite(void *out)
{

	pthread_mutex_lock(&mute);


    std::cout << " running....\n";
    try {
        // Create the socket
        ServerSocket server(30000);

        while (true) {
            ServerSocket in_sock;
            ServerSocket out_sock;
            server.accept(in_sock);
            server.accept(out_sock);

            // For multiple threading, you need to create
            // a new thread here and pass new_sock to it.
            // The thread will use new_sock to communicate
            // with the client.
            try 
            {
                ifstream ifs;
                ifs.open("sourcefile");
                while (!ifs.eof())
                {
                    string nextOutput = getString(20, ifs);

                    std::string response;
                    do
                    {
                        std::string newResponse;
                        out_sock << nextOutput;
                        in_sock >> newResponse;
                        response = newResponse;
                    } while (response != "ACK");
                }
                ifs.close();
            }
            catch(SocketException&) {
            }
        }
    }
    catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

	pthread_mutex_unlock(&mute);

    return 0;
}


string getString(int numChars, ifstream &is)
{
    stringstream ss;
    for (int i = 0; i < numChars; ++i)
    {
        char c = is.get();
        if (c != EOF)
            ss << c;
    }
    return ss.str();
}