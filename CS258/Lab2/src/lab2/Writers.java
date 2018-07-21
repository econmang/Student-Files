package lab2;

//This program writes different types of files.
//Random, Binary, and Text.
//Created 3/29/2004 for the lab 2 cs258 project.

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.security.InvalidParameterException;

public class Writers
{ 
	private final static int RECORDSIZE = 128;
	private final static int NAME_SIZE  = 30;
	private final static String spaces  = "                              ";

	// Keyboard input stream.
	private final static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String args[])
	{
		// File related variables variables.
		Writer out = null;
		String fileType = null, fileName = null;
		
		// Data variables.
		String  name;
		int age, recordNumber = 0;
		double salary;
		String  doMore;
		boolean quit, moreFiles;
		
		System.out.println("File writer program");
		do
		{
			try
			{
				do
				{
					System.out.print("Enter file type (text, binary, random): ");
					fileType = in.readLine().toLowerCase();
				}  while ( !("text".startsWith(fileType) ||
						"binary".startsWith(fileType) ||
						"random".startsWith(fileType))
						);

				System.out.print("Enter the file name: ");
				fileName = in.readLine().toLowerCase();
				switch (fileType.charAt(0))
				{
				case 't': out = new Text(fileName);
							break;
				case 'b': out = new Binary(fileName);
                    		break;
				case 'r': recordNumber = 0;
                    out = new Random( fileName, RECORDSIZE);
                    		break;
				default:  throw new InvalidParameterException();
				}

				do
				{  
					System.out.print("Enter Name: ");
					name = in.readLine() + spaces;
					name = name.substring(0,NAME_SIZE);

					age  = getAge();
					salary = getSalary();
					out.write(name, age, salary, recordNumber);
					recordNumber++;

					System.out.println("\n Type 'quit' to exit: ");

					doMore = in.readLine().toLowerCase();
					quit = (doMore.length()>0 && "quit".startsWith(doMore));
				}  while (!quit);
			}
			catch (InvalidParameterException e)
				{  
					System.out.println("Unknown case");
					System.exit(1);
				}
			catch (IOException e)
			{  
				System.out.println("I/O Error");
			}
			catch (Exception e)
			{  
				System.out.println("Illegal Entry");
			}
			finally 
			{ 
				try { out.close(); } catch(Exception e) {} }
			System.out.println("Another file? (y/n) ");

			try
			{  
				doMore = in.readLine().toLowerCase();
				moreFiles = (doMore.length()>0 && "yes".startsWith(doMore));
			}
			catch (Exception e) {moreFiles = false;}
		}  while (moreFiles);

		System.out.println("File write complete; data is in "+fileName+"\n");
		}   // End void main()

	// Method to input an age.
	private static int getAge()
	{
		int age = -1;
		String inputString = null;

		do
		{
			try
			{  
				System.out.print("Enter Age: ");
				inputString = in.readLine();
				age = Integer.parseInt(inputString);
				if (age<0 || age>100) throw new Exception();
				return age;
			}
			catch (Exception e) {System.out.println("Illegal age, try again");}
		}  while (true);
	}

	// Method to input a salary.
	private static double getSalary()
	{  
		double salary = -1;
		String inputString = null;

		do
		{
			try
			{
				System.out.print("Enter Salary: ");
				inputString = in.readLine();
				salary = Double.parseDouble(inputString);
				if (salary<0 || salary>1000000) throw new Exception();
				return salary;
			}
			catch (Exception e) {System.out.println("Illegal salary, try again");}
		}  while (true);
	}
}

	abstract class Writer
	{  
		public abstract void write(String name, int age, double salary, int record)
           throws IOException;
	
		public abstract void close();
	}

	class Random extends Writer
	{
		RandomAccessFile out;
		int recordSize;
		
		public Random(String fileName, int recordSize)
				throws FileNotFoundException
		{   
			out = new RandomAccessFile(fileName, "rw");
		}
		
		public void write(String name, int age, double salary, int record)
				throws IOException
		{   
			out.writeUTF(name);
			out.writeInt(age);
			out.writeDouble(salary);
			out.writeInt(record);
		}

		public void close()
		{   
			try
			{
				out.close();
			}
			catch(IOException io)
			{
				System.out.println("There was an error.");
			}
		}
	}

	class Binary extends Writer
	{
		DataOutputStream out = null;

		public Binary(String fileName) throws IOException
		{   
			out = new DataOutputStream(new FileOutputStream(fileName));
		}

		public void write(String name, int age, double salary, int record)
				throws IOException
		{   
			out.writeUTF(name);
			out.writeInt(age);
			out.writeDouble(salary);
			out.writeInt(record);
		}

		public void close()
		{	
			try
			{
				out.close();
			}
			catch(IOException io)
			{System.out.println("There was an error.");}
		}
	}

	class Text extends Writer
	{
		PrintWriter out = null;

		public Text(String filename) throws IOException
		{   
			out = new PrintWriter(new FileOutputStream(filename));
		}

		public void write(String name, int age, double salary, int record)
				throws IOException
		{   
			out.println(name);
			out.println(age);
			out.println(salary);
			out.println(record);
		}

		public void close()
		{   
			out.close();
		}
	}