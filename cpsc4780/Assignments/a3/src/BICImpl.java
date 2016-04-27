import java.io.*; 
import java.util.*; 
import java.rmi.*; 
import java.rmi.server.*; 
import java.math.BigInteger;
import java.util.Scanner;

public class BICImpl extends UnicastRemoteObject implements BIC
{    
	public BICImpl() throws RemoteException
	{
		
	}

	public BigInteger Calculate(BigInteger larg, char op, BigInteger rarg)
	{
		switch (op)
		{
			case '+': return larg.add(rarg);
			case '-': return larg.subtract(rarg);
			case '*': return larg.multiply(rarg);
			case '/': return larg.divide(rarg);
			default: return null;
		}
	}
	
    public static void main()
	{ 
		try
		{ 
			RMISecurityManager security = new RMISecurityManager(); 
			System.setSecurityManager(security);

			BICImpl server = new BICImpl(); 
			Naming.rebind("//localhost:2099/BICServer", server); 
			System.out.println("BICServer ready..."); 
		}
		
		catch (Throwable e)
		{ 
			System.err.println("exception: " + e); 
			System.exit(1); 
		} 
    }
}
