package lab2;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class RandReader
{
	public static void main(String[] args)
	{
		RandomAccessFile in;
		String name = "";
		int age = 0, record = 0;
		double salary = 0.0;
		
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter the name of the file you would like to examine: ");
		String fileName = scan.nextLine();
		scan.close();
		
		try
		{
			in = new RandomAccessFile(fileName, "r");
			
			name = in.readUTF();
			age = in.readInt();
			salary = in.readDouble();
			record = in.readInt();
			
			in.close();
			
			System.out.println("Employee Name: " + name);
			System.out.println("Employee Age: " + age);
			System.out.println("Employee Record Number: " + record);
			System.out.println("Employee Salary: " + salary);
		}
		catch(IOException io)
		{
			System.out.println("I/O Exception occurred.");
		}
	}
}
