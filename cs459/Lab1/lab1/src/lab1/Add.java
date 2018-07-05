/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.IOException;

public class Add extends Commands {
	public Add(){}
	public String runCommand(String[] args, ProcessList lis) throws ClassNotFoundException, IOException{
		long pid = System.currentTimeMillis() % 100000;
		Process proc = new Process(args,Thread.NORM_PRIORITY,pid);
		lis.enQueue(proc);
		return "Process " + proc.getName() + " added to batch.\n";
	}
}
