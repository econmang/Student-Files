/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

public class New extends Commands{
	public New(){ 
	}
	@Override
	public String runCommand(String[] args, ProcessList list){
		return "New batch initialized.";
	}
}