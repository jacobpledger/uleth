import java.io.*;
import java.net.*;
import java.util.*;

public class server
{
	public static void main(String args[])
	{
		ServerSocket serverSocket = null; //create server socket
		Socket clientSocket = null; //ceate client socket
		PrintWriter out = null; //writer to write to clientSocket
		String filename = "./inputfile";
		
		//attempt to initialize server socket
		try { serverSocket = new ServerSocket(4444); }
		catch (IOException e) {
			System.err.println("error initializing server socket");
			System.exit(-1);
		}
		
		Vector<Socket> sockets; //list of sockets
		sockets.addElement(new Socket());
		int size = sockets.size();
		try
		{ sockets[size] = serverSocket.accept(); }
		catch (IOException e) {
			System.err.println("error creating client socket");
			System.exit(-1);
		}
		
		
		
		/*
		//create client socket and connect
		try
		{ clientSocket = serverSocket.accept(); }
		catch (IOException e) {
			System.err.println("error creating client socket");
			System.exit(-1);
		}
		*/
		
		Vector<Thread> threads;
		//try {
			threads.addElement(new Thread());
		//}
		//catch (<#exception#>) {
		//	System.err.println("Unable to create new thread");
		//	System.exit(-1);
		//}
		
		//attempt to set up PrintWriter to write to the socket
		try { out = new PrintWriter(clientSocket.getOutputStream(), true); }
		catch (IOException e) {
			System.err.println("error setting up writing to socket");
			System.exit(-1);
		}		
		
		//read the file into the program and write to socket
		try
		{
			//set up file read
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
		catch (Exception e) {
			System.err.println("File read error");
		} //file read exception
		
		System.out.println("Transaction Complete");
	
		//attempt to close clientSocket
		try { clientSocket.close(); }
		catch (IOException e) {
			System.out.println("error closing clientSocket");
			System.exit(-1);
		}
		
		//attempt to close serverSocket
		try { serverSocket.close(); }
		catch (IOException e) {
			System.out.println("error closing serverSocket");
			System.exit(-1);
		}

	}
}