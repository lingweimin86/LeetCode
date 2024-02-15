#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ��λ����ʵ�ּӷ�
int bit_add(int x, int y)
{
	int sum = 0;
	int cf = 0;
	do
	{
		sum = x ^ y; // �޽�λ����ӽ��
	    cf = (x & y) << 1; // ��λ��Ϣ
		x = sum;
		y = cf;
	} while (cf > 0);

	return sum;
}

// ��λ����ʵ�ּ���
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

// �ҳ�һ����������2������1�ĸ���
// n & (n-1) ��������Сλ��1��Ϊ0
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
//��һ������������һ�����飬������1-Nÿ������������1�ĸ���
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

// ������ż���� ���� - 1�ĸ�������n-1�ĸ���+1�� ż��- 1�ĸ������� n>>1��1�ĸ���
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