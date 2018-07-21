package bits;

import java.io.Serializable;

public class BitMap implements Comparable, Serializable
{   
	public static final int  BITSIZE = 64;
    private long bitString;
 
    public BitMap()       // Three constructors.
    {	
    	clearAll();
    }
    public BitMap(String s) throws IndexOutOfBoundsException,ArithmeticException
    {	
    	if (s.length() > BITSIZE)
    	{
    		throw new IndexOutOfBoundsException();
    	}
    	
    	for(int i = 0; i < s.length(); i++)
    	{
    		char check = s.charAt(i);
    		
    		if (check == 't' || check == 'T')
    		{
    			bitString = bitString | (bitMask(s.length()-(i+1)));
    		}
    		else if (check == 'f' || check == 'F')
    		{
    			bitString = bitString & ~(bitMask(s.length()-(i+1)));
    		}
    		else
    		{
    			throw new ArithmeticException();
    		}
    	}
    }
    public BitMap(boolean[] bits) throws IndexOutOfBoundsException
    {	
    	if (bits.length > BITSIZE)
    	{
    		throw new IndexOutOfBoundsException();
    	}
    	
    	for(int i = 0; i < bits.length; i++)
    	{
    		if (bits[i] == true)
    		{
    			bitString = bitString | (bitMask(bits.length-(i+1)));
    		}
    		else if (bits[i] == false)
    		{
    			bitString = bitString & ~(bitMask(bits.length-(i+1)));
    		}
    	}
    }
 
    private long bitMask(int b)// Other class methods.
    {	
    	long mask = (1L << b);
    	return mask;
    }
    public void setBit(int b)
    {	
    	bitString = bitString | (bitMask(b));
    }
    public void clearBit(int b)
    {	
    	bitString = bitString & ~(bitMask(b));
    }
    public boolean checkBit(int b)
    {	
    	boolean check = false;
    	if (((bitString >> b) & 1) == 1)
    	{
    		check = true;
    		return check;
    	}
    	else
    	{
    		return check;
    	}
    }
    public int countTrue()
    {	
    	int trueCount = 0;
    	for (int i = 0; i < BITSIZE; i++)
    	{
    		if (checkBit(i) == true)
    		{
    			trueCount++;
    		}
    	}
    	return trueCount;
    }
    public void clearAll()
    {
    	for (int i = 0; i < BITSIZE; i++)
    	{
    		bitString = bitString & ~(bitMask(i));
    	}
    }
    public void setAll()
    {	
    	for (int i = 0; i < BITSIZE; i++)
    	{
    			bitString = bitString | (bitMask(i));
    	}
    }
 
    public int compareTo(Object bm) //For Comparable.
    {	
    	BitMap bitmap = (BitMap) bm;
    	if (this.countTrue() < bitmap.countTrue())
    	{
    		return -1;
    	}
    	else if (this.countTrue() > bitmap.countTrue())
    	{
    		return 1;
    	}
    	else
    	{
    		return 0;
    	}
    }
    public boolean equals(BitMap bm)
    {	
    	if(this.bitString == bm.bitString)
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }
    public String toString()
    {	
    	String a = "";
    	for (int i = BITSIZE-1; i > 0; i--)
    	{
    		if (checkBit(i) == true)
    		{
    			a = a + "t";
    		}
    		else if (checkBit(i) == false)
    		{
    			a = a + "f";
    		}
    	}
    	return a;
    }
}