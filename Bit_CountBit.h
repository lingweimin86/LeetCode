#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 用位运算实现加法
int bit_add(int x, int y)
{
	int sum = 0;
	int cf = 0;
	do
	{
		sum = x ^ y; // 无进位的相加结果
	    cf = (x & y) << 1; // 进位信息
		x = sum;
		y = cf;
	} while (cf > 0);

	return sum;
}

// 用位运算实现减法
int bit_minus(int x, int y)
{
	return bit_add(x, bit_add(~y, 1));
}

int bit_muti(int x, int y)
{
	int res = 0;
	while (y > 0)
	{
		if ((y & 1) != 0)
		{
			res = bit_add(res, x);
		}

		y = y >> 1; 
		x = x << 1;
	}
	return res;
}

// 找出一个整型数的2进制中1的个数
// n & (n-1) 可以让最小位的1变为0
int count_bits(int num)
{
	int count = 0;
	while (num != 0)
	{
		num = num & (num - 1);
		count++;
	}
	return count;
}
//给一个整数，返回一个数组，数组是1-N每个数二进制中1的个数
int* count_array_bits(int num)
{
	int* bits = new int[num + 1];
	bits[0] = 0;
	for (int i = 1; i <= num; i++)
	{
		bits[i] = bits[i & (i - 1)] + 1;
	}
	return bits;
}

// 利用奇偶数， 奇数 - 1的个数等于n-1的个数+1， 偶数- 1的个数等于 n>>1的1的个数
int* count_array_bits_2(int num)
{
	int* bits = new int[num + 1];
	bits[0] = 0;
	for (int i = 1; i <= num; i++)
	{
		bits[i] = ((i & 1) == 1 ? bits[i - 1] + 1 : bits[i >> 1]);
	}
	return bits;
}


void test_cout_bits()
{
	const int SIZE = 9;
	int nums[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int bitsCount[SIZE] = {};
	transform(nums, nums + SIZE, bitsCount, count_bits);

	cout << "the bits count is : ";
	for (auto i : bitsCount)
	{
		cout << to_string(i) << ", ";
	}

	cout << endl;
	// 
	int* nums2 = count_array_bits(SIZE);
	cout << "the bits count is : ";
	for (int i = 1; i <= SIZE; i++)
	{
		cout << to_string(nums2[i]) << ", ";
	}

	cout << endl;
	// 
	int* nums3 = count_array_bits_2(SIZE);
	cout << "the bits count is : ";
	for (int i = 1; i <= SIZE; i++)
	{
		cout << to_string(nums3[i]) << ", ";
	}
	cout << endl;

	// 
	int num4 = bit_add(7, 13);
	cout << "7 + 13 = " << num4 << endl;

	// 
	int num5 = bit_minus(7, 13);
	cout << "7 - 13 = " << num5 << endl;

	// 
	int num6 = bit_muti(7, 13);
	cout << "7 * 13 = " << num6 << endl;
}