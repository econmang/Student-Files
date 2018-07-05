package lab2;

import java.io.*;

//Parent class for programs to be run by the sequencer.
public abstract class Program implements Serializable
{   
 public final static long serialVersionUID = 1; 

	public final static int SUCCESS = 0;
	public final static int ILLEGAL_PARAMETER = 1;
	private String name;
	
	public Program(String name)
	{  this.name = name; }
	
	// Return process name
	public String getName() { return name; }
		
	// Abstract run method
	public abstract int run(PrintWriter out, String[] args)
		throws InterruptedException;

	// Fair share scheduling and check time limit interrupts
	public void schedule() throws InterruptedException
	{ 
		Thread.yield();  
		if (Thread.currentThread().isInterrupted())
			throw new InterruptedException();	}
		   
	// OS System call interface
	public String system()
	{
	    return "This method will be completed in a later lab";
	}
	
	// Method for orderly shutdown (overridden in applications in a later lab)
	public void terminate() {};
}
