#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int value;
	Node* next;

	Node& addNext(Node& next)
	{
		this->next = &next;
		return next;
	}
};

// 给两个链表的head，找出两个链表相交的节点，如不相交，则返回null
Node* get_intersection_node(Node* list1, Node* list2)
{
	Node* p1 = list1;
	Node* p2 = list2;

	while (p1 != p2)
	{
		p1 = ( p1 == nullptr ? list2 : p1->next);
		p2 = ( p2 == nullptr ? list1 : p2->next);
	}

	return p1;
}

// 升级： 如果两个链表任意一个可能有环，求相交结点，如不相交，则返回null
// 分析：有环(如相交，必然是两者都有环）
// 分3种情况: 1。两者不相交，
//           2。两者相交，入环点是同一个
//           3。两者相交，入环点不是同一个
Node* get_intersection_node_r(Node* list1, Node* list2)
{
	// TODO
	return nullptr;
}

Node* get_loop_node(Node* list)
{
	// TODO
	return nullptr;
}

void test_get_intersection_node()
{
	//  n11 -> n12 -> n13 ->
	//                      n14 -> n15
	//         n21 -> n22 ->
	//
	Node n11{ 1, nullptr }, n12{ 2, nullptr }, n13{ 3, nullptr }, n14{ 4, nullptr }, n15{ 5, nullptr };
	//n11.next = &n12, n12.next = &n13, n13.next = &n14, n14.next = &n15;
	n11.addNext(n12).addNext(n13).addNext(n14).addNext(n15);

	Node n21{ 1, nullptr }, n22{ 2, nullptr };
	//n21.next = &n22, n22.next = &n14;
	n21.addNext(n22).addNext(n14);

	Node* p1 = get_intersection_node(&n11, &n21);
	if (p1 != nullptr)
	{
		cout << to_string(p1->value) << endl;
	}
	else
		cout << "no intersection" << endl;

	// 
	Node n31{ 1, nullptr }, n32{ 2, nullptr }, n33{ 3, nullptr }, n34{ 4, nullptr };
	n31.next = &n32, n32.next = &n33, n33.next = &n34;

	Node n41{ 1, nullptr }, n42{ 2, nullptr }, n43{ 3, nullptr }, n44{ 4, nullptr };
	n41.next = &n42, n42.next = &n43, n43.next = &n44;

	Node* p2 = get_intersection_node(&n31, &n41);
	if (p2 != nullptr)
	{
		cout << to_string(p2->value) << endl;
	}
	else
		cout << "no intersection" << endl;

}