import java.io.*;
import java.net.*;
import java.util.*;

class sender implements Runnable
{
	Socket clientSocket;
	PrintWriter out;		
	
	public sender(Socket cs)
	{
		this.clientSocket = cs;
	}
	
	public void run()
	{
		//attempt to set up PrintWriter to write to the socket
		try 
		{
			out = new PrintWriter(clientSocket.getOutputStream(), true);
		}
		
		catch (IOException e)
		{
			System.err.println("error setting up writing to socket");
			System.exit(-1);
		}		
		
		//read the file into the program and write to socket
		try
		{
			//set up file read
			String filename = "./inputfile"; //what file to transmit
			FileInputStream fstream = new FileInputStream(filename);
			DataInputStream infile = new DataInputStream(fstream);
			
			while (infile.available() != 0) //while there are lines to be read...
			{
				//write to the clientSocket
				out.println(infile.readLine());
			}
			
			infile.close();
			out.close();
		}
		
		catch (Exception e)
		{
			System.err.println("File read error");
		}
		
		System.out.println("Transaction Complete");
		
		//attempt to close clientSocket
		try 
		{
			clientSocket.close();
		}
		
		catch (IOException e)
		{
			System.out.println("error closing clientSocket");
			System.exit(-1);
		}
	}
}

public class server
{	
	public static void main(String args[])
	{
		ServerSocket serverSocket = null; //create server socket
		Socket cSocket = null; //ceate client socket
		
		//attempt to initialize server socket
		try { serverSocket = new ServerSocket(4444); }
		catch (IOException e) {
			System.err.println("error initializing server socket");
			System.exit(-1);
		}
		
		int numconnections = 0;
		while (numconnections < 10) 
		{
			try
			{
				cSocket = serverSocket.accept();
			}
			catch (IOException e) {
				System.err.println("Error connecting cSocket");
			}
			//pass clientSocket to new thread & run
			new Thread(new sender(cSocket)).start();
			numconnections++;
		}
		
		//attempt to close serverSocket
		try
		{
			serverSocket.close();
		}
		
		catch (IOException e)
		{
			System.err.println("error closing serverSocket");
			System.exit(-1);
		}
	}
}