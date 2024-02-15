#include <iostream>
#include <string>

using namespace std;

// 给定一个数组，其他数字出现两次，只有一个数字出现一次，找出该数字
// 异或: A^A = 0    B^A^A = B^(A^A)   A^0 = A
int find_num_appear_once(int* nums, int len)
{
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result ^= nums[i];
	}

	return result;
}


void test_find_num_appear_once()
{
	int nums[] = { 1, 3, 1, 4, 5, 4, 5 };
	int ret = find_num_appear_once(nums, sizeof(nums) / sizeof(int));
	cout << "the num is : " << to_string(ret) << endl;
}