#pragma once

#include <iostream>
#include <string>
#include <list>
#include <unordered_set>
#include <stack>
#include "utility.h"

using namespace std;

// solution 1: 用hash_table保存之前的节点，但需要定义哈希函数因为节点不是基本类型
// solution 2: 用快慢指针

struct MyHash
{
	size_t operator()(const Node& n) const
	{
		size_t h1 = hash<int>{} (n.value);
		size_t h2 = hash<long long>{} ((long long)n.next);
		return h1 ^ (h2 << 1);
	}
};


// solution 1
bool is_list_a_circle(Node* head)
{
	unordered_set<Node, MyHash> mySet;
	while (head != nullptr)
	{
		if (mySet.contains(*head))
		{
			return true;
		}
	
		mySet.insert(*head);
		head = head->next;
	}

	return false;
}
// solution 2
bool is_list_a_circle_2(Node* head)
{
	Node* fastPtr = head;
	Node* slowPtr = head;

	while (fastPtr->next != nullptr && fastPtr->next->next != nullptr)
	{
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (slowPtr == fastPtr)
		{
			return true;
		}
	}

	return false;
}

Node* removeNthFromEnd(Node* head, int n) {
	Node* fast, * slow;
	fast = slow = head;

	while (n-- > 0)
	{
		fast = fast->next;
	}

	while (fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next;
		slow = slow->next;
	}

	fast = slow->next;
	slow->next = slow->next->next;
	delete fast;
	fast = nullptr;
	return head;
}

// LeetCode 143 重排链表
// 例1    1 -> 2 -> 3 -> 4
// ==>    1 -> 4 -> 2 -> 3
// 例2    1 -> 2 -> 3 -> 4 -> 5
// ==>    1 -> 5 -> 2 -> 4 -> 3
void reorderList(Node* head)
{
	stack<Node*> myStack;
}

void test_is_list_a_circle()
{
	Node n11{ 3, nullptr }, n12{ 2, nullptr }, n13{ 2, nullptr }, n14{ 4, nullptr };
	n11.next = &n12, n12.next = &n13, n13.next = &n14, n14.next = &n12; // is circle
	cout << (is_list_a_circle(&n11) ? "is a circle" : "is not a circle.") << endl;


	Node n21{ 4, nullptr }, n22{ 3, nullptr }, n23{ 4, nullptr }; 
	n21.next = &n22, n22.next = &n23; // not a circle
	cout << (is_list_a_circle(&n21) ? "is a circle" : "is not a circle.") << endl;

}

void test_reorderList()
{
	Node n11{ 1, nullptr }, n12{ 2, nullptr }, n13{ 3, nullptr }, n14{ 4, nullptr };
	n11.next = &n12, n12.next = &n13, n13.next = &n14;
	printList(&n11);

	Node n21{ 1, nullptr }, n22{ 2, nullptr }, n23{ 3, nullptr }, n24{ 4, nullptr }, n25{ 5, nullptr };
	n21.next = &n22, n22.next = &n23, n23.next = &n24, n24.next = &n25;
	printList(&n21);
}
