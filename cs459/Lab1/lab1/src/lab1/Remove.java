/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

public class Remove extends Commands{
	public Remove(){}
	public String runCommand(String[] args, ProcessList list){
		list.remove(Long.parseLong(args[0]));
		return "Process removed";
	}
}