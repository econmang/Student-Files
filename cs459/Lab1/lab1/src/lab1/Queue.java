/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.IOException;

public class Queue extends Commands{
	public Queue(){}
	public String runCommand(String[] args, ProcessList list)
			throws ClassNotFoundException, IOException, InstantiationException, IllegalAccessException{
		return list.toString();
	}
}