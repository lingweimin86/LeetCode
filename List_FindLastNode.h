#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

// 找出一个链表的倒数第K个节点
// solution 1: 定义一个数组，遍历链表时依次把节点添加到数组，最后根据下标来找到目标节点
// solution 2: 遍历一点链表，确定链表长度，然后再一次遍历链表，找到第 len-k+1个节点
// solution 3 (best): 定义两个指针指向头部，先让一个指针走K步，然后两个指针同时移动，
//  当第一个指针到达尾部时，第二个指针指向的节点即为所找节点
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