#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;
	Node* rand;
};

// ����һ����������ÿ���ڵ������nextָ�����һ��randָ�룬��ָ�����ָ����һ���ڵ��null�� ���ƴ�����

// solution 1: ��Ҫ��ռ临�Ӷȣ� �����ù�ϣ�������
// solution 2: Ҫ��ռ临�Ӷ�Ϊ O(1)

// TODO