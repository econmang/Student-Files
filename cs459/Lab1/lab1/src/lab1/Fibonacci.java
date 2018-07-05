/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

//Class to simulate a run time program.
//Generates fibonacci sequences of numbers.
import java.io.*;

public class Fibonacci extends Program
{  
	public final static long serialVersionUID = 1; 
	
	public Fibonacci() { super("Fibonacci Calculator"); }
	public int run(PrintWriter out, String[] args)
	{  
		long maxNumber = Long.parseLong(args[1]);
		if (maxNumber<1) return(ILLEGAL_PARAMETER);
		
		out.println(args[0]+ ": Sequence up to " + maxNumber + " numbers");
		if (maxNumber>=1) out.println(1);
		if (maxNumber>=2) out.println(1);
		long first = 1, second = 1, newNumber;
		for (int i=2; i<maxNumber; i++)
		{  
			newNumber = first + second;
			first = second;
			second = newNumber;
			out.println(newNumber);
		}
		return SUCCESS;
	}
	
	// small test driver for the Fibonacci program
	public static void main(String[] args) {
		Fibonacci f = new Fibonacci();
		String[] sa = {"Fibonacci", "12"};
		PrintWriter pw = new PrintWriter(System.out, true); // true => flush each output
		
		f.run(pw,sa);
	}
}