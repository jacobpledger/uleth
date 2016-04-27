// The description of the file
//
//
//

// FindClient.java 
import java.rmi.*; 
import java.rmi.server.*; 
public class FindClient { 
    public static void main(String args[]) { 
	try { 
	    RMISecurityManager security = new RMISecurityManager(); 
	    System.setSecurityManager(security); 

	    //Assuming the server is running on a host xyz    
	    String name = "rmi://" + "xyz.cs.uleth.ca:2099" + "/FindServer"; 
	    Find ref = (Find)Naming.lookup(name); 
	    String results = ref.findLine(args[0]); 
	    if (results == null) 
		System.err.println("** not found **"); 
	    else 
		System.out.println(results); 
	} catch (Throwable e) { 
	    System.err.println("exception: " + e); 
	    System.exit(1); 
	} 
    } 
}
