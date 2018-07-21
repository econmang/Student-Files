package lab1;

//Program to add and multiply complex numbers.
//Lab #1 for cs258; uses a class that handles complex numbers (Complex.java).

import java.io.*;

public class Calculator
{  public static void main(String[] args)
{  BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

   Complex num1, num2, result = new Complex();
   char    op;
   boolean more;

   System.out.println("\nComplex number calculation program\n");
   do
   {  num1 = readComplex(in);
      num2 = readComplex(in);

      op   = readChar(in, "Enter the operation '+, -, *, or /': ", "+-*/");
      switch (op)
      {  case '+':  result = num1.add(num2);
                    break;
         case '*':  result = num1.product(num2);
                    break;
         case '/':  result = num1.div(num2);
                    break;
         case '-':  result = num1.minus(num2);                      
      }
      System.out.println(num1+" "+op+" "+num2+" = "+result);
      more = (readChar(in, "Perform another calculation? (y/n): ", "yn") !='n');
              
   } while (more);
        
   System.out.println("\n\nCalculation program completed\n");
}
  
// Method to read a complex number
public static Complex readComplex(BufferedReader in)
{  
  String  token;

   while (true)
   {     System.out.print("Enter a complex number: ");   
         try 
         {  token = in.readLine();
            return Complex.parseComplex (token);  
         } 
         catch (Exception exception) 
         {  System.out.println("llegal Format - enter 'a+bi' and try again");  }
   }

}
  
// Method to read the first character of a string
public static char readChar(BufferedReader in, String prompt, String chars)
{
   String token;
   char   value;
   
   while (true)
   {  try
      {  System.out.print(prompt);
         token = in.readLine();
         value = token.toLowerCase().charAt(0);
         if (chars.indexOf(value)<0) throw new NumberFormatException();
         return value;
      }
      catch (Exception exception) 
      { System.out.println("Illegal - try again"); }
   }
}
}