/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;
import console.*;
import java.io.*;

/** Class to test the OS Console class */
public class Cli implements CommandListener
{
	ProcessList lis = new ProcessList();
	OSConsole console;
	
	public static void main(String[] args)
	{
		new Cli();
	}
	
	public Cli()
	{
		console = new OSConsole("Batch Sequencer");
		console.setCommandListener(this);
		//console.login();
		console.write("--->> ");
	}

	@Override
	public void commandReceived(String command)
	{
		// Add your code to process each command here
		String[] argData = command.split(" ");
		argData[0] = argData[0].substring(0,1).toUpperCase() + argData[0].substring(1).toLowerCase();
		String[] args = new String[argData.length - 1];
		System.arraycopy(argData, 1, args, 0, args.length);
		try{
			Class<?> classname = Class.forName("lab1."+ argData[0]);
			Commands classInstance = (Commands) classname.newInstance();
			console.writeLine(classInstance.runCommand(args, lis));
		}
		catch (Throwable t){
			if (t instanceof ClassNotFoundException) {
				console.writeLine("ClassNotFoundException for " + command);
			} else if (t instanceof IOException) {
				console.writeLine("IOException for " + command);
			} else if (t instanceof InstantiationException) {
				console.writeLine("InstantiationException for " + command);
			} else if (t instanceof IllegalAccessException) {
				console.writeLine("IllegalAccessException for " + command);
			} else {
				console.writeLine("Thrown Exception for " + command);
				t.printStackTrace();
			}
		}
		console.write("--->> ");
	}	
}