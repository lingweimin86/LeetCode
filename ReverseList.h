#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

// 反转一个链表
Node* reverse_list(Node* list)
{
	Node* pre = nullptr;
	Node* cur = list;
	Node* next = list->next;
	while (next != nullptr)
	{
		cur->next = pre;
		pre = cur;
		cur = next;
		next = next->next;
	}

	cur->next = pre;
	return cur;
}

void test_reverse_list()
{
	Node n11{ 1, nullptr }, n12{ 2, nullptr }, n13{ 3, nullptr }, n14{ 4, nullptr }, n15{ 5, nullptr };
	n11.next = &n12, n12.next = &n13, n13.next = &n14, n14.next = &n15;

	Node* p1 = reverse_list(&n11);
	while (p1 != nullptr)
	{
		cout << p1->value << ", ";
		p1 = p1->next;
	}

}