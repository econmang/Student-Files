package stacks;

import java.util.StringTokenizer;

public class Calculator
{
	public static void main(String[] args)
	{
		Calculator calc = new Calculator("-1 + 2");
		System.out.println("The Result of -1 + 2 is: ");
		calc.calculate();
		
		Calculator calcTwo = new Calculator("1*2*3*4+5");
		System.out.println("The Result of 1*2*3*4+5 is: ");
		calcTwo.calculate();
		
		Calculator calcThree = new Calculator("(4+3) + (2*4)");
		System.out.println("The result of (4+3) + (2*4) is: ");
		calcThree.calculate();
		
		Calculator calcFour = new Calculator("1+2+a");
		System.out.println("The result of 1+2+a is: ");
		calcFour.calculate();
	}

	private Stack<Double> operand;
	private Stack<Character> operator;
	private String expression;

	public Calculator(String exp)
	{
		operand = new Stack<Double>();
		operator = new Stack<Character>();
		this.expression = exp;
	}

	public void evaluate()
	{
		try
		{
			double num2 = operand.pop();
			double num1 = operand.pop();
			
			switch (operator.pop())
			{
			case '*':
				operand.push(num1*num2);
				break;
			case '/':
				operand.push(num1/num2);
				break;
			case '+':
				operand.push(num1+num2);
				break;
			case '-':
				operand.push(num1-num2);
				break;
			default:
				String num1Check = Double.toString(num1);
				String num2Check = Double.toString(num2);
				for (int i = 0; i < num1Check.length();i++)
				{
					if (Character.isDigit(num1Check.charAt(i)) == false)
					{
						throw new StackException();
					}
				}
				for (int i = 0; i < num2Check.length();i++)
				{
					if (Character.isDigit(num2Check.charAt(i)) == false)
					{
						throw new StackException();
					}
				}
				System.err.println("Operator doesn't exist.");
			}
		}
		catch (StackException se)
		{
			System.err.println("The stack is empty.");
			return;
		}
	}
	public void calculate()
	{
		if(expression == null)
		{
			System.err.println("No expression.");
			return;
		}
		
		expression = expression.replaceAll("\\s+","");

		StringTokenizer stk = new StringTokenizer(expression, "+-/*()", true);

		try
		{
			while(stk.hasMoreTokens())
			{
				String token = stk.nextToken();
				boolean signOk = true;
				int sign = 1;
				switch (token)
				{
					case "(": operator.push('(');
						  break;
					case ")": while(operator.look() != '(')
						  {
							evaluate();
						  }
						  operator.pop();
						  break;
					case "-": 
						  sign = -1;
						  if(signOk)
						  {
							  Double numToken = Double.parseDouble(stk.nextToken())*sign;
							  operand.push(numToken);
							  break;
						  }
						  while((!operator.isEmpty()) && "+-*/".indexOf(operator.look())>=0)
						  {
							evaluate();
						  }
						  operator.push(token.charAt(0));
						  break;
					case "+": 
						  while((!operator.isEmpty()) && "+-*/".indexOf(operator.look())>=0)
						  {
							evaluate();
						  }
						  operator.push(token.charAt(0));
						  break;
					
					case "*": while((!operator.isEmpty()) && "*/".indexOf(operator.look())>=0)
						  {
							evaluate();
						  }
						  operator.push(token.charAt(0));
						  break;
					case "/": while((!operator.isEmpty()) && operator.look() == '*'||operator.look() == '/')
						  {
							evaluate();
						  }
						  operator.push(token.charAt(0));
						  break;
					default:
						operand.push(Double.parseDouble(token));
						break;
				}
			}
			while(operator.isEmpty() == false)
			{
				evaluate();
			}
			System.out.println(operand.pop());
		}
		catch (StackException se)
		{
			System.err.println("Error on stack. Exiting.. ");
			se.printStackTrace();
			System.exit(1);
		}
		catch(Exception e)
		{
			System.err.println("Illegal input");
			System.exit(1);
		}
	}
}