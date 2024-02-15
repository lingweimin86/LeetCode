#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

// �ҳ�һ������ĵ�����K���ڵ�
// solution 1: ����һ�����飬��������ʱ���ΰѽڵ���ӵ����飬�������±����ҵ�Ŀ��ڵ�
// solution 2: ����һ������ȷ�������ȣ�Ȼ����һ�α��������ҵ��� len-k+1���ڵ�
// solution 3 (best): ��������ָ��ָ��ͷ��������һ��ָ����K����Ȼ������ָ��ͬʱ�ƶ���
//  ����һ��ָ�뵽��β��ʱ���ڶ���ָ��ָ��Ľڵ㼴Ϊ���ҽڵ�
Node* find_last_element_of_list_n(Node* list, int n)
{
	if (list == nullptr) return nullptr;

	Node *p1, *p2;
	p1 = p2 = list;

	while(n-- > 0)
	{
		p1 = p1->next;
		if (p1 == nullptr)
		{
			return nullptr;
		}
	}

	while (p1 != nullptr)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	return p2;

}

void test_find_last_element_of_list_n()
{
	Node n11{ 1, nullptr }, n12{ 2, nullptr }, n13{ 3, nullptr }, n14{ 4, nullptr }, n15{ 5, nullptr };
	n11.next = &n12, n12.next = &n13, n13.next = &n14, n14.next = &n15;

	Node* p1 = find_last_element_of_list_n(&n11, 3);
	if (p1 != nullptr)
	{
		cout << p1->value << endl; // 3
	}

}