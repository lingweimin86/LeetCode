#include <algorithm>
#include <iostream>

using namespace std;

// Ԥ������Ŀ

// ��Ŀ1��С��һ�������Σ���ɫΪ����̣�С������Ϳ���κθ������ε���ɫ
// ����Ҫ���������ɫ���ұ��Ǻ�ɫ������һ�����У���Ҫʵ������Ҫ����ʹ�õ���СͿ�Ĵ���
// �� RGGRRG  ��СͿ�Ĵ���Ϊ2�����Ϊ GGGRRR
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


// ��Ŀ2����һ������Ԫ�ص�ֵΪ1������1�������������ε����߳�
// ��
// 1 0 1 1 1
// 1 0 1 0 1
// 1 1 1 1 1
// 0 1 1 0 1
// ���߳�Ϊ3

// ��Ŀ3�� �Ѿ���һ���ȸ��ʵĺ�������13-21֮���������ʵ��һ�������ȸ��ʷ���30-50
// ˼·�� ���13-21����λ����������λ������1��С����λ������0�����ӵ��һ���ȸ��ʷ���0��1�ĺ���
//       �ֱ���30-50�Ķ����ƣ���01�����ȸ��ʵ�����ÿ��������λ�������ɵ���Ҳ�ǵȸ��ʵ�


void test_data_cleaning()
{
	char array[] = "RGGRRG";
	cout << "green and red problem " << green_red(array, strlen(array)) << endl;
}