// Description of the file.
//
//
//
//
//
// Find.java 
import java.rmi.*; //Import the rmi package. 

public interface Find extends Remote { //Must extend java.rmi.Remote.
    //Each method must throw java.rmi.RemoteException. 
    public String findLine(String keyword) throws RemoteException; 
}
