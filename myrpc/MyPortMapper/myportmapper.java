/* Quick note on naming:
 Classes_Are_Named_Like_This (except for myportmapper...)
 variables_are_named_like_this
 functionsAreNamedLikeThis
 IMPORTANT_VARIABLES_ARE_NAMED_LIKE_THIS
 all if possible, things like run() have to be named the way they are
 */
/*
 main simply accepts connections from hosts, when a connection is accepted, a new thread is 
 spawned to receive the service. Upon reception, a thread is spawned for each host in the system 
 and the new service is sent to all other hosts
 */

import java.io.*;
import java.net.*;
import java.util.ArrayList;

class myportmapper
{    
    
    public static void main(String args[])
	{
		// declare sockets to receive connections on
        ServerSocket listener = null;
		Socket receiver_socket = null;

        // declare and initilize list for registered services
        ArrayList<service> registered_services = new ArrayList<service>();
        registered_services.clear();
		
        // blocking receive listening for a connection
        try
		{
			listener = new ServerSocket(10111);
		}
		catch (Exception e)
		{
			System.err.println("Error initializing ServerSocket listener");
		} // end try catch
        
		// receive connections for service requests
		while(true)
		{
			try
			{
				receiver_socket = listener.accept();
                new Thread(new receiver(receiver_socket, registered_services)).start();
			}
			catch (Exception e)
			{
				System.err.println("Error connecting receiver_socket");
                e.printStackTrace();
			} // end try catch
                        
        } // end while
    } // end main
} // end class myportmapper
