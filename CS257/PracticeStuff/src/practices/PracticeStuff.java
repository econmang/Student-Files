package practices;

public class PracticeStuff
{
	static int pickRandom(int min, int max)
	{
		int randInt = (int) Math.random()*min + max;
		return randInt;
	}
	static void main(String[] args)
	{
		int a = pickRandom(3, 10);
		System.out.println(a);
	}
}
