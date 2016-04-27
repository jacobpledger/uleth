// The description of the file
//
//
//
//
//
// FindImpl.java 
import java.io.*; 
import java.util.*; 
import java.rmi.*; 
import java.rmi.server.*; 

public class FindImpl extends UnicastRemoteObject implements Find { 
    //constructor 
    private Vector list = new Vector(); 
    public FindImpl(String aFile) throws RemoteException {
	try { 
	    FileReader fr = new FileReader(aFile); 
	    BufferedReader br = new BufferedReader(fr); 
	    String s = null; //convert a line into a vector element 
	    while ((s = br.readLine()) != null) 
		list.addElement(s); 
	    fr.close(); 

	} catch (Throwable e) { 
	    System.err.println("exception"); 
	    System.exit(1); 
	} 
    } //end of constructor 

    public String findLine(String keyword) { 
	if (keyword == null) 
	    return null; 
	keyword = keyword.toLowerCase(); 
	int n = list.size(); 
	for (int i = 0; i < n; i++) { //For each line in the list 
	    String line = (String)list.elementAt(i); 
	    if (line.toLowerCase().indexOf(keyword) != -1) //Is "keyword" part of the line? 
		return line; //Return the line containing "keyword" 
	} return null; 
    } 
    
    public static void main(String args[]) { 
	try { 
	    RMISecurityManager security = new RMISecurityManager(); 
	    System.setSecurityManager(security); 
	    String aFile= args[0]; 
	    FindImpl server = new FindImpl(aFile); 
	    Naming.rebind("//127.0.0.1:2099/FindServer", server); 
	    System.out.println("FindServer ready..."); 
	} catch (Throwable e) { 
	    System.err.println("exception: " + e); 
	    System.exit(1); 
	} 
    } 
}
