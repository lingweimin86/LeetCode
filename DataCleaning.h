#include <algorithm>
#include <iostream>

using namespace std;

// 预处理题目

// 题目1：小明一排正方形，颜色为红和绿，小明可以涂改任何个正方形的颜色
// 现在要让左边是绿色，右边是红色，给定一个序列，求要实现上述要求所使用的最小涂改次数
// 如 RGGRRG  最小涂改次数为2，结果为 GGGRRR
int count_green_or_red(char* array, int start, int len, char c)
{
	int count = 0;
	for (int i = start; i < len; i++)
	{
		if (array[i] == c)
		{
			count++;
		}
	}

	return count;
}

int green_red(char* array, int len)
{
	int* num = new int[len + 1];

	for (int i = 0; i < len + 1; i++)
	{
		num[i] = count_green_or_red(array, 0, i, 'R') + count_green_or_red(array, i, len, 'G');
		cout << "i: " << i << " num[i]: " << num[i] << endl;
	}

	return *min_element(num, num + len + 1);
}


// 题目2：有一个矩阵，元素的值为1，求由1连起来的正方形的最大边长
// 如
// 1 0 1 1 1
// 1 0 1 0 1
// 1 1 1 1 1
// 0 1 1 0 1
// 最大边长为3

// 题目3： 已经有一个等概率的函数返回13-21之间的数，求实现一个函数等概率返回30-50
// 思路， 求出13-21的中位数，大于中位数返回1，小于中位数返回0，则就拥有一个等概率返回0和1的函数
//       分别求30-50的二进制，用01函数等概率地生成每个二进制位，则生成的数也是等概率的


void test_data_cleaning()
{
	char array[] = "RGGRRG";
	cout << "green and red problem " << green_red(array, strlen(array)) << endl;
}