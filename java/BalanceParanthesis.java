import java.util.Stack;

public class BalanceParanthesis
{
	// Static stuff:
	public static void main(String[] args)
	{
		runTest("({[]})", true);
		runTest("", true);
		runTest("())", false);
		runTest("(()", false);
		runTest("[}", false);
		runTest("}", false);
		runTest("()()()(({}))[()]", true);

		return;
	}

	public static void runTest(String test, boolean correctResult)
	{
		boolean actualResult = checkBalance(test);

		StringBuilder builder = new StringBuilder("Checking string: \"" + test + "\"");

		while(builder.length() < 40)
		{
			builder.append('.');
		}

		if(actualResult == correctResult)
		{
			builder.append("Passed");
		}
		else
		{
			builder.append("FAILED");
		}

		System.out.println(builder.toString());
	}

	public static boolean checkBalance(String string)
	{
		Stack<Character> parenStack = new Stack<Character>();

		if(string == null)
		{
			return true;
		}

		for(int index = 0; index < string.length(); index++)
		{
			char temp = string.charAt(index);

			switch(temp)
			{
				case '(':
					parenStack.push(temp);
					break;

				case '[':
					parenStack.push(temp);
					break;

				case '{':
					parenStack.push(temp);
					break;

				case ')':
					if(parenStack.size() > 0 &&
					   parenStack.peek() == '(')
					{
						parenStack.pop();
					}
					else
					{
						return false;
					}
					break;

				case ']':
					if(parenStack.size() > 0 &&
					   parenStack.peek() == '[')
					{
						parenStack.pop();
					}
					else
					{
						return false;
					}
					break;

				case '}':
					if(parenStack.size() > 0 &&
					   parenStack.peek() == '{')
					{
						parenStack.pop();
					}
					else
					{
						return false;
					}
					break;
			}
		}

		if(parenStack.size()  == 0)
		{
			return true;
		}

		//Leftover open parens:
		return false;
	}
}