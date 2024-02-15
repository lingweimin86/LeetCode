#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

//          ƽ��ʱ�临�Ӷ�    ������     ����      �ռ临�Ӷ�     �ȶ���      �Ƚ��㷨
// ð������    N^2             N           N^2           1           Y           Y
// ѡ������    N^2            N^2          N^2           1           N           Y
// ��������    N^2             N           N^2           1           Y           Y
// ϣ������   nlogn-N^2       N^1.3        N^2           1           N           Y
// �鲢����    nlogn          nlogn       nlogn          n           Y           Y
// ��������    nlogn          nlogn        N^2          logn         N           Y
// ������      nlogn          nlogn       nlogn          1           N           Y
// ��������    N+K            N+K          N+K           K           Y           N
// Ͱ����      N+C            N            N^2          N+K          Y           N
// ��������    N*K            N*K          N*K          N+K          Y           N

// �ȶ��ԣ� ��ͬ��С������Ԫ���Ƿ���ά��ԭ���Ĵ���

// ���ɣ� ����������ѡ�������㷨��С������������죬��������������죬 
// ���Ի��ʹ�ã����磬�ھֲ��ò����������������ÿ�������
// �����ȶ����� �鲢���� �������ȶ����� ��������


void print_array(int* num, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << to_string(num[i]) << ", ";
	}

	cout << endl;
}


// ��������Ԫ��ʹ�ô��Ԫ��λ�ں���λ�ã�ÿһ�ֽ����󣬱�������Ԫ�ر����õ�����β��
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

// ÿһ���ҳ���С/���Ԫ�أ��������ͷ��/β��Ԫ�ؽ��н���
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

// ��������
// 1����׼����������β�����ָ�ָʾ������-1��Ȼ��������鲢���������ж�
//      A.�����ǰԪ��С�ڵ��ڻ�׼������ָ�ָʾ������һλ
//      B.��A�Ļ����ϣ������ǰԪ���±���ڷָ�ָʾ���±�ʱ����ǰԪ����ָ�ָʾ����ָԪ�ؽ���

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

// ��������
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

	for (int d = 0; d < digits; d++) // N������
	{
		fill(counter.begin(), counter.end(), 0);
		// ��counterͳ�Ƹ�λ�������¸�ѭ����ʮλ����λ������
		for (int i = 0; i < len; i++)
		{
			int index = ((num[i] / (int)pow(10, d) ) % 10);
			counter[index]++;
		}

		for (int i = 1; i < 10; i++)
		{
			counter[i] += counter[i - 1]; // �ۼӼ�������ʱ������ֵ-1ΪԪ���ڵ�N���������±�
		}

	    // ������������num��Ԫ����tmp������
		for (int i = len - 1; i >= 0; i--)
		{
			int index = ((num[i] / (int)pow(10, d)) % 10);
			int pos = counter[index] - 1;
			tmp[pos] = num[i];
			counter[index]--; //��֤��һ��ͬbucket��Ԫ���������
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
