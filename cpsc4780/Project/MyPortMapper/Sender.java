import java.io.*;
import java.net.*;

class sender implements Runnable
{
    Socket sender_socket;
    String service_to_broadcast;

    public sender(Socket ss, String s)
    {
        // use socket already created in this thread
        sender_socket = ss;
        this.service_to_broadcast = s;
    } // end constructor

    public void run()
    {
        try
        {
            PrintWriter out = new PrintWriter(sender_socket.getOutputStream(),true);
            out.println(service_to_broadcast);
        }
        catch (Exception e)
        {
            System.err.println("Error setting up PrintWriter to sender_socket");
            e.printStackTrace();
        } // end try catch
    } // end run
} // end class sender