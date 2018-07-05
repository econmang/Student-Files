/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab2;

//Class to simulate a runtime program
//Finds first n primes
import java.io.*;

public class Primes extends Program{
	public Primes() { super("Find Primes"); }
	
	public final static long serialVersionUID = 1;
	
	@Override
	public int run(PrintWriter out, String[] args) 
			throws InterruptedException{
		long n = Long.parseLong(args[1]);
		if (n<1) {return(ILLEGAL_PARAMETER);}
		else{
			out.println("The first " + n + " primes");
			int count=0;
		    int curr=2;
		    while(count!=n)
		    {
		        boolean prime=true;
		        for (int i=2;i<=Math.sqrt(curr);i++)
		        {
		            if (curr%i==0)
		            {
		                prime = false;
		                break;
		            }

		    }
		        if (prime)
		        {
		            count++;
		            out.println(curr);
		        }
		        curr++;
		    }
		    return 0;
		}
	}
	
}