package bits;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Test 
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter the name of the file of the test: ");
		String fileName = scan.nextLine();
		String userAnswers = null;
		try
		{
			BufferedReader in = new BufferedReader(new FileReader(fileName));
			System.out.println("Answer with a T or F");
			
			String question = in.readLine();
			while(question != null)
			{
				System.out.println(question);
				String currentAnswer = scan.nextLine();
				userAnswers = userAnswers + currentAnswer;
				question = in.readLine();
			}
			in.close();
			
			String finalUserAnswers = userAnswers.substring(4); //used to delete "null" from String
			BitMap bmpUser = new BitMap(finalUserAnswers);
			
			DataInputStream answerKey = new DataInputStream(new FileInputStream("ans.bin"));
			String currentString = answerKey.readUTF();
			answerKey.close();
			BitMap key = new BitMap(currentString);
			
			int countCorrect = 0;
			for(int i = 0; i < 25; i++)
			{
				boolean keyCheck = key.checkBit(i);
				boolean userCheck = bmpUser.checkBit(i);
				if (keyCheck == userCheck)
				{
					countCorrect++;
				}
			}
			if (countCorrect > 18)
			{
				System.out.println("Congratulations! You got " + countCorrect + "/25 questions correct!");
			}
			else
			{
				System.out.println("Better luck next time! You got " + countCorrect + "/25 questions correct.");
			}
		}
		catch (FileNotFoundException fnf)
		{
			System.out.println("File was not found.");
		}
		catch(IOException io)
		{
			System.out.println("There was an I/O error.");
		}
		catch(NullPointerException npe)
		{
			
		}
	}
}
