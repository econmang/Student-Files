package practice;

import java.util.*;
import java.io.*;
import java.math.*;

public class Practice
{
	public static int closerToAZ(char c, int roll)
	{
		int a = (Math.abs('a' - c) + roll);
		int z = (Math.abs('z' - c) + roll);
		if (z == 0) 				{return -1;}
		else if (a == 0) 			{return a; }
		else if(a < z)	     		{return -a;}
		else if (z < a)  			{return z; }
		else if (a == z && a != 0)  {return -a;}
		else			  			 return 0;
	}
	public static void main(String args[])
	{
        Scanner in = new Scanner(System.in);
        System.out.println("Enter Magic Phrase: ");
        String magicPhrase = in.nextLine();
        String bilboMoves = "+";
        int roll = 0;
        
        for (int i = 0; i < magicPhrase.length(); i++)
        {
        	String newMoves = "";
			if (magicPhrase.charAt(i) == ' ')
		    	{
		        	bilboMoves += ">.<";
		    	}
			else
			{
				int diff = 0;
				char letter = Character.toLowerCase(magicPhrase.charAt(i));
			    if (i == 0)
			    {
			    	diff = closerToAZ(letter,roll);
			    	if(diff == 0)
			    	{
			    		bilboMoves += ".";
			    	}
			    	else if (diff < 0)
			    	{
			    		int count = 0;
			    		for(int fmoves = 0; fmoves < Math.abs(diff); fmoves++)
			    		{
			    			newMoves += "-";
			    			count++;
			        	}
			    		roll += -count;
			        }
			    	else
			    	{
			    		int count = 0;
			    		for(int bmoves = 0; bmoves < diff; bmoves++)
			    		{
			    			newMoves += "+";
			    			count++;
			        	}
			    		roll += count;
			    	}
			    }
			    else
			    {
			    	char lastLetter = Character.toLowerCase(magicPhrase.charAt(i-1));
			    	if (lastLetter == letter)
			    	{
			    		bilboMoves += ".";
			    	}
			    	else if(lastLetter != letter)
			    	{
			    		diff = closerToAZ(letter,roll);
			    		if(diff == 0)
			    		{
			    			bilboMoves += ".";
			    		}
			    		else if (diff < 0)
			    		{
			    			int count = 0;
			    			for (int a = 0; a < Math.abs(diff); a++)
			    			{
			    				newMoves += "-";
			    				count++;
			    			}
			    			roll += -count;
			    			if (roll > 26)
				    		{
				    			roll = roll - 26;
				    		}
				    		if (roll < -26)
				    		{
				    			roll = roll + 26;
				    		}
			    		}
			    		else
			    		{
			    			int count = 0;
			    			for (int b = 0; b < diff; b++)
			    			{
			    				newMoves = "+";
			    				count++;
			    			}
			    			roll += count;
			    			if (roll > 26)
				    		{
				    			roll = roll - 26;
				    		}
				    		if (roll < -26)
				    		{
				    			roll = roll + 26;
				    		}
			    		}
			    	}
			    }
			    
			}
		}
        System.out.println(bilboMoves);
	}
}