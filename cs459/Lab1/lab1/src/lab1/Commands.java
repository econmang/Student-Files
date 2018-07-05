/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.*;

public abstract class Commands{
	protected static PrintWriter pw = null;
	
	public abstract String runCommand(String[] args, ProcessList lis)
		throws ClassNotFoundException, IOException, InstantiationException, IllegalAccessException;
	
	public ProcessList proc = new ProcessList();
}