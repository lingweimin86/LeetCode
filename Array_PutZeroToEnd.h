#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;
// 给一个整型数组,将所有为零的元素移到数组的末尾，保持其他元素的顺序不变
void put_values_to_end(int* num, int len, int value)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len ; j++)
		{
			if (num[i] == value && num[j] != value)
			{
				num[i] = num[j];
				num[j] = value;
				break;
			}
		}
	}
}

void test_put_values_to_end()
{
	int num1[] = {0, 1, 0, 3, 12, 0};
	put_values_to_end(num1, sizeof(num1) / sizeof(int), 0);
	for (auto i : num1)
	{
		cout << i << ", ";
	}
	cout << endl;

	int num2[] = {9, 1, 9, 1, 12};
	put_values_to_end(num2, sizeof(num2) / sizeof(int), 1);
	for (auto i : num2)
	{
		cout << i << ", ";
	}

	cout << endl;
}