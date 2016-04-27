import java.rmi.*; 
import java.rmi.server.*;
import java.math.BigInteger;
import java.util.Scanner;

public class BICClient { 
    public static void main()
	{ 
		try
		{ 
			RMISecurityManager security = new RMISecurityManager(); 
			System.setSecurityManager(security); 
			    
			String name = "rmi://" + "localhost:2099" + "/BICServer"; 
			BIC calculator = (BIC)Naming.lookup(name);
			
			Scanner input = new Scanner(System.in);
			BigInteger larg = null;
			String str_op;
			char op = '+';
			BigInteger rarg = null;
			
			while(true)
			{
				System.out.println("Please input your operation: ");
				try
				{
					larg = input.nextBigInteger();
					str_op = input.next();
					op = str_op.charAt(0);
					rarg = input.nextBigInteger();
				}
			
				catch (NumberFormatException e)
				{
					System.err.println("Argument must be an integer");
					System.exit(1);
				}
	
				BigInteger result = calculator.Calculate(larg,op,rarg);
				String s1 = larg.toString();
				String s2 = Character.toString(op);
				String s3 = rarg.toString();
				String output = null;
				output.concat(s1);
				output.concat(s2);
				output.concat(s3);
				System.out.println(output);
			}
		}
		
		catch (Throwable e)
		{ 
			System.err.println("exception: " + e); 
			System.exit(1); 
		} 
    } 
}
