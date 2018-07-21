package bits;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class CreateTest
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter the name of the file of the test: ");
		String fileName = scan.nextLine();
		String answerKey = null;
		try
		{
			BufferedReader in = new BufferedReader(new FileReader(fileName));
			System.out.println("Answer with a T or F");
			
			String question = in.readLine();
			while(question != null)
			{
				System.out.println(question);
				String currentAnswer = scan.nextLine();
				answerKey = answerKey + currentAnswer;
				question = in.readLine();
			}
			in.close();
			
			String finalAnswerKey = answerKey.substring(4); //used to delete "null" from String
			DataOutputStream out = new DataOutputStream(new FileOutputStream("ans.bin"));
			out.writeUTF(finalAnswerKey);
			out.close();
			System.out.println("The answers were saved to file: \"ans.bin\"");
		}
		catch (FileNotFoundException fnf)
		{
			System.out.println("File was not found.");
		}
		catch(IOException io)
		{
			System.out.println("There was an I/O error.");
		}
	}
	
}
