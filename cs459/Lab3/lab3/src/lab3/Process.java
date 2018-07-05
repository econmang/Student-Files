package lab3;

import java.io.*;

//Class to represent a process.
public class Process
{  

	private String[] args;       // The calling arguments.
	private long id;             // Process Id number (pid).
	private int  priority;       // Priority.
	private long startTime;      // Process start time.
	private long endTime;        // End time after process completes.
	private Stati  status;       // Process status.
	
	Class<?>   className;           // Bytecode name of class.
	Program classInstance;       // Class instance that can be called.
	
	public Process next;		  // Links for next and previous list entries.
	public Process previous;
	
	// Constructors and methods.
	public Process(String[] args, int priority, long id)
			throws ClassNotFoundException, IOException {
		this.args = args;
		this.priority = priority;
		this.id = id;
		this.status = Stati.IDLE;
		className = Class.forName("lab3."+getName());
	}
	                            
	public String run(PrintWriter out) 
			throws InstantiationException, IllegalAccessException, InterruptedException {
		classInstance = (Program) className.newInstance();
		startTime = System.currentTimeMillis();
		status = Stati.RUNNING;
		classInstance.run(out, args);
		status = Stati.TERMINATED;
		endTime = System.currentTimeMillis();
		return getName() + " ran successfully time = " + getRunTime() + " milliseconds\n";
	}
	public void setPriority(int priority) {
		this.priority = priority;
	}
	public long getId() {
		return id;
	}
	public int getPriority() {
		return priority;
	}
	public String getName() {
		return args[0] = args[0].substring(0, 1).toUpperCase() + args[0].substring(1);
	}
	public String[] getArgs() {
		String[] argCpy = new String[args.length-1];
		System.arraycopy(args, 1, argCpy, 0, argCpy.length);
		return argCpy;
	}
	/*	
		Process.getRuntime() returns zero if the status is IDLE (or if startTime == 0). 
		It returns System.currentTimeMillis() – startTime if the status is RUNNING (or if endTime == 0). 
		It returns endTime – startTime otherwise.
	*/	
	public long getRunTime() {
		if (this.getStatus().equals("Idle")){return 0;}
		else if(this.getStatus().equals("Running")){
			return System.currentTimeMillis() - startTime;
		}
		else{
			return endTime - startTime;
		}
	}
	public String getStatus() {
		switch(status)
		{
			case RUNNING: return "Running";
			case WAIT: return "Wait";
			case IDLE: return "Idle";
			case TERMINATED: return "Terminated";
			case ABORTED: return "Aborted";
			default: return "N/A";
		}
	}
	
	public void setStatus(Stati status) {
		this.status = status;
	}
	
	public String toString() {
		String prog = String.format("%-15s %-10d %-10s %-10d %-10d %-5d", getName(), getId(), getStatus(), getRunTime(), getPriority(), Integer.parseInt(args[1]));
		return prog;
	}
}
