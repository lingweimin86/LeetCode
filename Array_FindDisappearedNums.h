#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 给一个整型数组,长度为n,里取的值的范围为1到n, 找出未出现过的数值
vector<int> find_disappearred_nums(int* array, int len)
{
	for (int i = 0; i < len ; i++)
	{
		int index = (array[i] > 0 ? array[i]: -array[i]) - 1;
		if (array[index] > 0)
		{
			array[index] = -array[index]; // set to negative as a flag
		}
	}

	vector<int> result;
	for (int i = 0; i < len; i++)
	{
		if (array[i] > 0)
		{
			result.push_back(i + 1);
		}
		else
		{
			array[i] = -array[i]; // revert back the original value
		}
	}

	return result;
}

void test_find_disappearred_nums()
{
	int num1[] = { 4, 3, 2, 7, 8, 2, 3, 1 };
	vector<int> results = find_disappearred_nums(num1, sizeof(num1) / sizeof(int));
	for (auto i : results)
	{
		cout << i << ", ";
	}
	cout << endl;

	int num2[] = { 1, 1 };
	results = find_disappearred_nums(num2, sizeof(num2) / sizeof(int));
	for (auto i : results)
	{
		cout << i << ", ";
	}
}