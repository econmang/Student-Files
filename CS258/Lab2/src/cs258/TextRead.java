package cs258;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

public class TextRead extends Keyboard
{  
	Scanner in = new Scanner(System.in);
	
	
	public TextRead(String filename) 
	{
		try
		{
			in = new Scanner(new FileInputStream(filename));
		}
		catch(IOException io){System.out.println("There was an I/O Error.");}
		
	}
	public boolean close()
	{	
		if (endOfFile())
		{
			in.close();
			return true;
		}
		else
		{
			return false;
		}
	}
	public boolean endOfFile() 
	{	
		if(in.hasNextLine())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
} 
