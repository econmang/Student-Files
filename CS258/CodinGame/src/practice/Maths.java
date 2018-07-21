package practice;

public class Maths
{
	public int closerToAZ(char check, int roll)
	{
		int a = Math.abs('a' - check) + roll;
		int z = Math.abs('z' - check) + roll;
		if(a < z){return a;	}
		else if (z < a) {return -z;}
		else if (a == z){ return a;}
		else if (a == 0) {return a;}
		else if (z == 0) {return -1;}
		else return 0;
	}
	public static void main(String[] args)
	{
		System.out.println('a' - 'b');
		System.out.println('a' - 'z');
	}
}
