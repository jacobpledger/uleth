import java.rmi.*; //Import the rmi package. 
import java.math.BigInteger;

public interface BIC extends Remote
{
    public BigInteger Calculate(BigInteger larg, char op, BigInteger rarg) throws RemoteException;

}
