package practice;

import java.util.*;
import java.io.*;
import java.math.*;

public class Bilbo
{
	public static void main(String args[])
	{
        Scanner in = new Scanner(System.in);
        System.out.println("Enter Magic Phrase: ");
        String magicPhrase = in.nextLine();
        String bilboMoves = "+";
        
        for (int i = 0; i < magicPhrase.length(); i++)
        {
        	String newMoves = "";
			String rollBack = "";
			if (magicPhrase.charAt(i) == ' ')
		    	{
		        	bilboMoves += ">.<";
		    	}
			else
			{
				char lowerLetter = Character.toLowerCase(magicPhrase.charAt(i));
			    int diff = 'a' - lowerLetter;
			    if(diff == 0)
			    	{
			    		bilboMoves += ".";
			        }
			    else if(diff < 0)
			    	{
			    		for(int fmoves = 0; fmoves < Math.abs(diff); fmoves++)
			    		{
			    			newMoves += "+";
			        	}
			    		for(int brolls = 0; brolls < Math.abs(diff); brolls++)
			        	{
			        		rollBack += "-";
			        	}
			        	bilboMoves += newMoves + "." + rollBack;
			        }
				}
			}
        System.out.println(bilboMoves);
        in.close();
	}
}