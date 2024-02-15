#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

//string decode_string(string decodedString)
//{
//	int bracketCount = 0;
//	bool hasSubBracket = false;
//	bool bracketsStart = false;
//	int bracketLevel = 0;
//	int num = 0;
//	int bracketStart = 0;
//	int bracketEnd = 0;
//	int subBracketStart = 0;
//	int subBracketEnd = 0;
//	for (size_t i = 0; i < decodedString.size(); i++)
//	{
//		if (decodedString[i] == '[')
//		{
//			num = decodedString[i - 1] - '0';
//			bracketCount++;
//			bracketLevel++;
//
//			if (bracketLevel == 1)
//			{
//				bracketStart = i - 1;
//			}
//			else if (bracketLevel == 2)
//			{
//				subBracketStart = i - 1;
//			}
//		}
//		else if (decodedString[i] == ']')
//		{
//			bracketLevel--;
//
//			if (bracketEnd == 0)
//			{
//				bracketEnd = i + 1;
//			}
//			if (bracketLevel == 1)
//			{
//				subBracketEnd = i + 1;
//			}
//		}
//
//		if (bracketCount > 0 && bracketLevel == 0) // a close bracket
//		{
//			if (bracketCount > 1) // has sub brackets
//			{
//				string decodedStr = decode_string(decodedString.substr(subBracketStart, subBracketEnd - subBracketStart));
//				decodedString.replace(subBracketStart, subBracketEnd - subBracketStart, decodedStr);
//			}
//			else // no sub brackets
//			{
//				string subStr = decodedString.substr(bracketStart - 2, bracketEnd - bracketStart - 3);
//				ostringstream ss;
//				ss << decodedString.substr(0, bracketStart);
//				while (num-- > 0)
//				{
//					ss << subStr;
//				}
//				ss << decodedString.substr(bracketEnd);
//				return ss.str();
//			}
//		}
//		
//	}
//}

// use stack
string decode_string(string input)
{
	stack<char> myStack;
	deque<char> myDeq;

	for (size_t i = 0; i < input.size(); i++)
	{
		myStack.push(input[i]);
		if (input[i] == ']')
		{
			// pop the pattern num[text] to stack
			while (!isdigit(myStack.top()))
			{
				myDeq.push_front(myStack.top());
				myStack.pop();
			}

			int num = myStack.top() - '0'; // take *num*
			myStack.pop();

			for (int n = 0; n < num; n++)
			{
				for (int j = 1; j < myDeq.size() - 1; j++) // ignore '[' ']'
				{
					myStack.push(myDeq[j]);
				}
			}
			myDeq.clear();
			
		}
	}

	deque<char> deq;
	while (!myStack.empty())
	{
		char top = myStack.top();
		myStack.pop();
		deq.push_front(top);
	}

	return string(deq.begin(), deq.end());
}

void test_decode_string()
{
	string s = "3[a]2[bc]";
	cout << decode_string(s) << endl; // aaabcbc

	s = "3[a2[c]]";
	cout << decode_string(s) << endl; // accaccacc

	s = "abc3[cd]xyz";
	cout << decode_string(s) << endl; // abccdcdcdxyz
}