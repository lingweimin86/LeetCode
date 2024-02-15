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

// 给定一个链表，它的每个节点除了有next指针后还有一个rand指针，这指针可以指向任一个节点或null， 复制此链表

// solution 1: 不要求空间复杂度， 可以用哈希表来解决
// solution 2: 要求空间复杂度为 O(1)

// TODO