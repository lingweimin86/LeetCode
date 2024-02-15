#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctype.h>
#include <vector>

using namespace std;

string addTwoStringNums(string num1, string num2)
{
	stringstream ss;
	int carry = 0;
	int i = num1.length() - 1;
	int j = num2.length() - 1;
	for (; i >= 0 || j >= 0 || carry == 1;)
	{
		int x = (i < 0 ? 0 : num1[i] - '0');
		int y = (j < 0 ? 0 : num2[j] - '0');
		ss << ((x + y + carry) % 10);
		carry = (x + y + carry) / 10;
		i--;
		j--;
	}

	string s = ss.str();
	reverse(s.begin(), s.end());
	return s;
}

int myAtoi(string s) {

	constexpr int maxIntDiv = INT_MAX / 10;
	constexpr int maxIntMod = INT_MAX % 10;
	bool isNegative = false;
	bool isbegin = false;
	int num = 0;
	bool isContinue = true;
	for (auto iter = s.begin(); iter != s.end() ; iter++)
	{
		if (*iter >= '0' && *iter <= '9')
		{
			isbegin = true;
			int toAdd = (*iter - '0');

			if (num > maxIntDiv || (num == maxIntDiv && toAdd > maxIntMod))
			{
				return isNegative ? INT_MIN : INT_MAX;
			}

			num = num * 10 + toAdd;
		}
		else if (*iter == ' ' && isbegin == false)
		{
			continue;
		}
		else if (*iter == '+' && isbegin == false)
		{
			isbegin = true;
		}
		else if (*iter == '-' && isbegin == false)
		{
			isbegin = true;
			isNegative = true;
		}
		else {
			break;
		}
	}

	return num * (isNegative ? -1 : 1);
}

int maxArea(vector<int>& height) 
{
	if (height.size() <= 1)
	{
		return 0;
	}

	int maxValue = 0;
	for (int i = 0, j = height.size() - 1; i < j;)
	{
		int lowerHeight = min(height[i], height[j]);
		maxValue = max(maxValue, lowerHeight * (j - i));
		lowerHeight == height[i] ? i++: j--;
	}
	return maxValue;
}



struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}    
	ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode *fast, *slow;
	fast = slow = head;

	while (n-- > 0)
	{
		fast = fast->next;
	}

	while (fast->next != nullptr)
	{
		fast++;
		slow++;
	}

	fast = slow->next;
	slow->next = slow->next->next;
	delete fast;
	fast = nullptr;
	return head;
}

void test_addTwoStringNums()
{
	//string sum = addTwoStringNums("345", "789");
	//cout << sum << endl;

	//cout << myAtoi(" -42") << endl;
	//cout << myAtoi(" 42sssss") << endl;
	//cout << myAtoi(" s42sssss") << endl;
	//cout << myAtoi(to_string(INT32_MAX)) << endl;
	//cout << myAtoi("-91283472332") << endl;
	cout << myAtoi("-2147483648") << endl;
	cout << myAtoi("-2147483647") << endl;
	cout << myAtoi("-2147483649") << endl;
	cout << myAtoi("-21474836480") << endl;
	cout << myAtoi("2147483646") << endl;
	cout << myAtoi("2147483647") << endl;
	cout << myAtoi("2147483648") << endl;
	cout << myAtoi("21474836470") << endl;
	cout << myAtoi("9147483647") << endl;

	vector<int> vec1 = { 1,8,6,2,5,4,8,3,7 };
	cout << maxArea(vec1) << endl;

	vector<int> vec2 = { 1, 1 };
	cout << maxArea(vec2) << endl;
}