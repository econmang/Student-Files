/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.*;

public class Cat extends Commands {
	public Cat(){}
	@Override
	public String runCommand(String[] args, ProcessList lis) throws ClassNotFoundException, IOException {
		String str = null;
		StringBuffer buff = new StringBuffer();
		try{
			File file = new File(args[0]);
			BufferedReader in = new BufferedReader(new FileReader(file.getCanonicalPath()));
			while((str = in.readLine()) != null){
				buff.append(str);
				buff.append("\n");
			}
			in.close();
		}
		catch(IOException IOE){
			return "Error: File Does Not Exist.";
		}
		return buff.toString();
	}
}