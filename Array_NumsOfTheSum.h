#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;
// 给一个整型数组和一个和，输出数组中和是这个值的两个数的下标
pair<int, int> get_nums_of_the_sum(int* array, int len, int sum)
{
	unordered_map<int, int> valueIndexMap;

	for (size_t i = 0; i < len; i++)
	{
		int valueToSearch = sum - array[i];
		if (valueIndexMap.contains(valueToSearch))
		{
			return make_pair(valueIndexMap[valueToSearch], i);
		}
		else
		{
			valueIndexMap[array[i]] = i;
		}
	}

	return make_pair(-1, -1);
}

void test_get_nums_of_the_sum()
{
	int s1[] = { 2, 4, 8 };
	cout << "input : " << s1 << endl;
	pair actual1 = get_nums_of_the_sum(s1, sizeof(s1)/sizeof(int), 10);
	cout << "output : " << to_string(actual1.first) << ", " << to_string(actual1.second) << endl;

	int s2[] = { 1, 9, 3, 8 };
	cout << "input : " << s2 << endl;
	pair actual2 = get_nums_of_the_sum(s2, sizeof(s2) / sizeof(int), 17);
	cout << "output : " << to_string(actual2.first) << ", " << to_string(actual2.second) << endl;

	int s3[] = { 1, 9, 3, 8 };
	cout << "input : " << s3 << endl;
	pair actual3 = get_nums_of_the_sum(s3, sizeof(s3) / sizeof(int), 5);
	cout << "output : " << to_string(actual3.first) << ", " << to_string(actual3.second) << endl;
}