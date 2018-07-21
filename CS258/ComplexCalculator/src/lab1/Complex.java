package lab1;

import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class Complex
{  
	private double real, imaginary;

	public Complex()
	{
		real = this.real;
		imaginary = this.imaginary;
	}
	
	public Complex(double real, double imaginary)
	{
		this.real = real;
		this.imaginary = imaginary;
	}
	
	public String toString()
	{
		String complexNum = "";
		if (imaginary > 0)
		{
			complexNum = real + "+" + imaginary + "i";
		}
		else if (imaginary < 0)
		{
			complexNum = real + "-" + imaginary +"i";
		}
		else if (imaginary == 0)
		{
			complexNum = Double.toString(real);
		}
		else if (real == 0)
		{
			complexNum = Double.toString(imaginary);
		}
		return complexNum;
	}
	
	public Complex add( Complex c)
	{  
		return new Complex (real+c.real, imaginary+c.imaginary);
	}
	
	public Complex minus(Complex c)
	{
		return new Complex (real-c.real, imaginary-c.imaginary);
	}
	
	public Complex product(Complex c)
	{
		double realPart = (real * c.real) - (imaginary*c.imaginary);
		double imaginaryPart = (imaginary*c.real) + (real*c.imaginary);
		Complex newComp = new Complex(realPart, imaginaryPart);
		return newComp;
	}
	
	public Complex div(Complex c)
	{
		double realNumerator = (real*c.real)-(imaginary * (-1*(c.imaginary)));
		double imagNumerator = (imaginary * c.real) + (real+c.imaginary);
		double denominator = (c.real*c.real) - (c.imaginary *(-1 * c.imaginary));
		realNumerator /= denominator;
		imagNumerator /= denominator;
		Complex newComp = new Complex(realNumerator,imagNumerator);
		return newComp;
	}
	
	public static Complex parseComplex(String str) 
			throws NumberFormatException, NoSuchElementException
	{

		StringTokenizer stk = new StringTokenizer(str,"-+i", true);
		int sign = 1;
		double real = 0.0; 
		double imaginary = 0.0;
		String token = stk.nextToken();
		
		switch (token.charAt(0))
		{
			case '-': sign = -1;
			case '+': token = stk.nextToken();
			default: real = Double.parseDouble(token)*sign;
		}
		if (stk.hasMoreTokens())
		{
			token = stk.nextToken();
			switch (token.charAt(0))
			{
				case '-': sign = -1;
				case '+': sign = 1;
						  token = stk.nextToken();
				default: imaginary = Double.parseDouble(token)*sign;
			}
		}
		
		return new Complex(real, imaginary);
	}
}
