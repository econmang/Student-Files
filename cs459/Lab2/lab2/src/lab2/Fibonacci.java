package lab2;

//Class to simulate a run time program.
//Generates fibonacci sequences of numbers.
import java.io.*;

public class Fibonacci extends Program
{  

	private static final long serialVersionUID = 1L;

	public Fibonacci() { super("Fibonacci Calculator"); }

	public int run(PrintWriter out, String[] args) 
			throws InterruptedException
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
			this.schedule();
		}
		return SUCCESS;
	}
}
