package sort;

import java.util.Scanner;

public class MinMaxArray
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int[] intStore = new int[10];
		int next;
		int maxArray;
		int minArray;
		for(int i = 0; i <10; i++)
		{
			System.out.println("Enter a value: ");
			next = scan.nextInt();
			intStore[i] = next;
		}
		maxArray = intStore[0];
		minArray = intStore[0];
		for(int a = 0; a<10; a++)
		{
			if (intStore[a]< minArray)
			{
				minArray = intStore[a];
			}
			else 
				minArray = minArray;
			if (intStore[a]>maxArray)
			{
				maxArray = intStore[a];
			}
			else
			{
				maxArray = maxArray;
			}
		}
		System.out.println("The max value of the array is " + maxArray);
		System.out.println("The min value of the array is " + minArray);
	}
}
