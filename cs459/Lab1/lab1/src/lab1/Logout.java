/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

public class Logout extends Commands{

	Logout(){}
	@Override
	public String runCommand(String[] args, ProcessList list){
		System.exit(0);
		return null;
	}
}