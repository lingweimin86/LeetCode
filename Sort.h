#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

//          平均时间复杂度    最好情况     最坏情况      空间复杂度     稳定性      比较算法
// 冒泡排序    N^2             N           N^2           1           Y           Y
// 选择排序    N^2            N^2          N^2           1           N           Y
// 插入排序    N^2             N           N^2           1           Y           Y
// 希尔排序   nlogn-N^2       N^1.3        N^2           1           N           Y
// 归并排序    nlogn          nlogn       nlogn          n           Y           Y
// 快速排序    nlogn          nlogn        N^2          logn         N           Y
// 堆排序      nlogn          nlogn       nlogn          1           N           Y
// 计数排序    N+K            N+K          N+K           K           Y           N
// 桶排序      N+C            N            N^2          N+K          Y           N
// 基数排序    N*K            N*K          N*K          N+K          Y           N

// 稳定性， 相同大小的两个元素是否能维持原来的次序

// 技巧： 按样本体量选择排序算法，小样本插入排序快，大样本快速排序快， 
// 可以混合使用，例如，在局部用插入排序，在总体上用快速排序
// 考虑稳定性用 归并排序， 不考虑稳定性用 快速排序


void print_array(int* num, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << to_string(num[i]) << ", ";
	}

	cout << endl;
}


// 交换相邻元素使得大的元素位于后置位置，每一轮结束后，本轮最大的元素被放置到数组尾部
void bubble_sort(int* num, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (num[j] > num[j + 1]) {
				int k = num[j];
				num[j] = num[j+1];
				num[j + 1] = k;
			}
		}
	}
}

// 每一轮找出最小/大的元素，跟数组的头部/尾部元素进行交换
void select_sort(int* num, int len)
{
	for (int i = 0; i < len; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < len; j++)
		{
			if (num[j] < num[minIndex])
			{
				minIndex = j;
			}
		}

		if (i != minIndex)
		{
			int k = num[i];
			num[i] = num[minIndex];
			num[minIndex] = k;
		}
	}
}

// 快速排序
// 1。基准数放置数组尾部，分割指示器等于-1，然后遍历数组并进行以下判断
//      A.如果当前元素小于等于基准数，则分割指示器右移一位
//      B.在A的基础上，如果当前元素下标大于分割指示器下标时，当前元素与分割指示器所指元素交换

void quick_sort(int* num, int len)
{
	if (len <= 1)
		return;

	int base = num[len - 1]; // now just set to the last element, it can be random set
	int partition = -1;

	for (int i = 0; i < len; i++)
	{
		if (num[i] <= base)
		{
			partition++;
			if (i > partition)
			{
				int k = num[i];
				num[i] = num[partition];
				num[partition] = k;
			}
		}
	}

	quick_sort(num, partition);
	quick_sort(num + partition + 1, len - partition - 1);
}

// 基数排序
void bucket_sort(int* num, int len)
{
	//int* tmp = new int[len];
	//int* counter = new int[10];
	vector<int> tmp(len, 0);
	vector<int> counter(10, 0);

	int maxNum = *max_element(num, num + len);
	int digits = 0; 
	
	while (maxNum != 0)
	{
		maxNum = maxNum / 10;
		digits++;
	}

	for (int d = 0; d < digits; d++) // N轮排序
	{
		fill(counter.begin(), counter.end(), 0);
		// 在counter统计个位个数（下个循环是十位，百位。。）
		for (int i = 0; i < len; i++)
		{
			int index = ((num[i] / (int)pow(10, d) ) % 10);
			counter[index]++;
		}

		for (int i = 1; i < 10; i++)
		{
			counter[i] += counter[i - 1]; // 累加计数，此时计数的值-1为元素在第N轮排序后的下标
		}

	    // 由右至左排列num的元素至tmp数组中
		for (int i = len - 1; i >= 0; i--)
		{
			int index = ((num[i] / (int)pow(10, d)) % 10);
			int pos = counter[index] - 1;
			tmp[pos] = num[i];
			counter[index]--; //保证下一个同bucket的元素往左放置
		}

		copy(tmp.begin(), tmp.end(), num);
	}

	//delete[] tmp;
	//delete[] counter;
}

void test_sort()
{
	using clock = chrono::steady_clock;
	clock::duration cost;
	clock::time_point begin, end;

	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	const int SIZE = 20;
	int num[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	shuffle(num, num + SIZE, default_random_engine(seed));

	int num1[SIZE];
	memcpy(num1, num, sizeof(num));

	// bubble sort
	cout << "before sort: ";
	print_array(num1, SIZE);

	begin = clock::now();
	bubble_sort(num1, SIZE);
	cout << "cost: " << to_string(chrono::duration_cast<chrono::microseconds>(clock::now() - begin).count()) << " micro seconds" << endl;

	cout << "bubble sort: ";
	print_array(num1, SIZE);

	// select sort
	memcpy(num1, num, sizeof(num));
	cout << "before sort: ";
	print_array(num1, SIZE);

	begin = clock::now();
	select_sort(num1, SIZE);
	cout << "cost: " << to_string(chrono::duration_cast<chrono::microseconds>(clock::now() - begin).count()) << " micro seconds" << endl;

	cout << "select sort: ";
	print_array(num1, SIZE);

	// quick sort
	memcpy(num1, num, sizeof(num));
	cout << "before sort: ";
	print_array(num1, SIZE);

	begin = clock::now();
	quick_sort(num1, SIZE);
	cout << "cost: " << to_string(chrono::duration_cast<chrono::microseconds>(clock::now() - begin).count()) << " micro seconds" << endl;

	cout << "quick sort: ";
	print_array(num1, SIZE);

	// bucket sort
	memcpy(num1, num, sizeof(num));
	cout << "before sort: ";
	print_array(num1, SIZE);

	begin = clock::now();
	bucket_sort(num1, SIZE);
	cout << "cost: " << to_string(chrono::duration_cast<chrono::microseconds>(clock::now() - begin).count()) << " micro seconds" << endl;

	cout << "bucket sort: ";
	print_array(num1, SIZE);
}
