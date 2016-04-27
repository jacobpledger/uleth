import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args)
	{
        Socket clientSocket = null;
        BufferedReader in = null;
		
		//attempt to set up socket & ability to read from that socket
        try {
            clientSocket = new Socket("Server", 4444);
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        }
		
		catch (UnknownHostException e) {
            System.err.println("Error connecting to Server");
            System.exit(-1);
        }
		
		catch (IOException e) {
            System.err.println("Couldn't set up BufferedReader");
            System.exit(-1);
        }
		
		String filename = "outputfile";
		FileOutputStream fstream = null;
		try { fstream = new FileOutputStream(filename); }
		catch (FileNotFoundException fnf) {
			System.err.println("File not found");
			System.exit(-1);
		}
		
		DataOutputStream outfile = new DataOutputStream(fstream);
		PrintWriter out = new PrintWriter(fstream);
		String line = null;
		
		//communicate with server
		boolean done = false;
		while(!done)
		{
			try {line = in.readLine(); }
			catch (IOException e) {
				System.err.println("error reading file from server");
				System.exit(-1);
			}
			
			if (line != null)
			{
				//output to file
				out.print(line);
			}
			else { done = true; }
        }
		
        try{ in.close(); }
		catch (IOException e) {
			System.err.println("error stopping read");
			System.exit(-1);
		}
		
		try { outfile.close(); }
		catch (IOException e) {
			System.err.println("error closing outfile");
			System.exit(-1);
		}
		
        try { clientSocket.close(); }
		catch (IOException e) {
			System.err.println("error closing clientSocket");
			System.exit(-1);
		}
		
		System.out.println("Transaction Complete, please check outputfile");
    }
}