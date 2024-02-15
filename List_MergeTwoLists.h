#pragma once

#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Node
{
	int value;
	Node* next;
};


Node* merge_two_lists(Node* list1, Node* list2)
{
	Node head = { 0, nullptr };
	Node* p = &head;

	while (list1 != nullptr && list2 != nullptr)
	{
		if (list1->value <= list2->value)
		{
			p->next = list1;
			list1 = list1->next;
		}
		else
		{
			p->next = list2;
			list2 = list2->next;
		}

		p = p->next;
	}

	if (list1 != nullptr)
	{
		p->next = list1;
	}

	if (list2 != nullptr)
	{
		p->next = list2;
	}

	return head.next;
}

// 题目 给定一个搜索二叉树，把它转换成一个双向排序的链表，左子树 当作 next, 右子树 当作 prev
// 如       5
//         / \
//        3   6 
//       / \   \
//      2   4   7
//
// 转化后  2=3=4=5=6=7 ,返回结点2
// TODO

void test_merge_two_lists()
{
	Node n1{ 1, nullptr }, n2{ 2, nullptr }, n3{ 4, nullptr };
	n1.next = &n2, n2.next = &n3;
	Node* list1 = &n1;

	Node n4{ 1, nullptr }, n5{ 3, nullptr }, n6{ 4, nullptr };
	n4.next = &n5, n5.next = &n6;
	Node* list2 = &n4;

	Node* p = merge_two_lists(list1, list2);
	Node* t = p;
	while (t != nullptr)
	{
		cout << to_string(t->value) << ", ";
		t = t->next;
	}

}