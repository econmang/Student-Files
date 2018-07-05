package lab3;

/*
 * Evan Conley, Jacob Cromwell, Mike Coley
 * Prof. Nordquist
 * CS 459
 * Lab 3
 * */

import java.io.*;
import java.net.Socket;

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
			throw new InterruptedException("Process Aborted");	}
		   
	// OS System call interface
	/*public String system()
	{
	    return "This method will be completed in a later lab";
	}*/
	
	// Method for orderly shutdown (overridden in applications in a later lab)
	public void terminate() {};
	
	/*Creates a client socket connection to the OS server class*/
	public String system(String call){
		try{
			Socket sock = new Socket("127.0.0.1", SystemCall.PORT);
			PrintWriter writer = new PrintWriter(sock.getOutputStream(),true);
			BufferedReader bin = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			writer.println(call); 
			String response = bin.readLine();	
			sock.close();
			return response;
			
			
		}catch(IOException ioe){
			ioe.printStackTrace();
			return "Error";
		}
	}
}
