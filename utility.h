#pragma once
#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* next;
	bool operator==(const Node& rhs) const
	{
		return this->value == rhs.value && this->next == rhs.next;
	}
} ListNode;

void printList(Node* head)
{
    while(head != nullptr)
    {
        cout << to_string(head->value) << " ";
    }
    cout << endl;
}

