#pragma once

#include <iostream>
#include <string>

using namespace std;

void merge_two_arrays(int* num1, int m, int* num2, int n)
{
	int* p1 = num1 + m - 1; // point to the last element of num1
	int* p2 = num2 + n - 1; // point to the last element of num2
	int i = m + n - 1; // the pos to put the element
	while ( i >= 0)
	{
		if (p1 == nullptr || *p1 <= *p2)
		{
			num1[i] = *p2;
			if (p2 == num2)
			{
				break;
			}
			else
			{
				p2--;
			}
		}
		else
		{
			num1[i] = *p1;
			if (p1 == num1) 
			{
				p1 = nullptr; // num1 has sorted, now just need to fix num2
			}
			else 
			{
				p1--;
			}

		}
		i--;
	}
}

void test_merge_two_arrays()
{
	int num1[] = {1, 2, 3, 0, 0, 0};
	int num2[] = { 2, 5, 6 };
	merge_two_arrays(num1, 3, num2, 3);
	for (auto i : num1)
	{
		cout << to_string(i) << ", ";
	}

	cout << endl;

	int num3[] = { 7, 8, 9, 0, 0, 0 };
	int num4[] = { 2, 5, 6 };
	merge_two_arrays(num3, 3, num4, 3);
	for (auto i : num3)
	{
		cout << to_string(i) << ", ";
	}

	cout << endl;

	int num5[] = { 1, 2, 3, 0, 0, 0 };
	int num6[] = { 4, 5, 6 };
	merge_two_arrays(num5, 3, num6, 3);
	for (auto i : num5)
	{
		cout << to_string(i) << ", ";
	}

}