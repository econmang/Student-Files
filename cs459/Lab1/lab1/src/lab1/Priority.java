/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.IOException;

public class Priority extends Commands {
	public Priority() {
	}

	@Override
	public String runCommand(String[] args, ProcessList list) 
			throws ClassNotFoundException, IOException, InstantiationException, IllegalAccessException{
		int newPriority = Integer.parseInt(args[1]);
		if (newPriority < Thread.MIN_PRIORITY || newPriority > Thread.MAX_PRIORITY-1)
			return "ERROR: Priority must be between: " + Thread.MIN_PRIORITY + "-" + (Thread.MAX_PRIORITY-1);
		list.setPriority(Long.parseLong(args[0]), newPriority);
		return list.toString();
	}

}