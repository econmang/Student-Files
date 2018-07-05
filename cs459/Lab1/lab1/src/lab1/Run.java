/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.*;

public class Run extends Commands {
	public Run() {
	}

	@Override
	public String runCommand(String[] args, ProcessList lis)
			throws ClassNotFoundException, IOException, InstantiationException, IllegalAccessException {
		File file = new File(args[0] + ".bat");
		PrintWriter write = new PrintWriter(file.getCanonicalFile());
		String str = "";
		while (!lis.isEmpty()) {
			str += lis.deQueue().run(write);
		}
		write.flush();
		write.close();
		if (str == "")
			return "Error: Queue is empty";
		else
			return str;
	}
}