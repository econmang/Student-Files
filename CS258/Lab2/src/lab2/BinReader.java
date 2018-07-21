package lab2;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

public class BinReader
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		
		System.out.println("Enter the name of the file you would like to examine: ");
		String fileName = scan.nextLine();
		scan.close();
		
		DataInputStream in;
		String name = "";
		int age = 0;
		int record = 0;
		double salary = 0.0;
		
		try
		{
			in = new DataInputStream(new FileInputStream(fileName));
			
			name = in.readUTF();
			age = in.readInt();
			salary = in.readDouble();
			record = in.readInt();
			
			in.close();
			
			System.out.println("Employee Name: " + name);
			System.out.println("Age: " + age);
			System.out.println("Employee Record Number: " + record);
			System.out.println("Employee Salary: " + salary);
		}
		catch (IOException io)
		{
			System.out.println("There was an I/O Error.");
		}
	}
}
