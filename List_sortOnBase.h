#include <iostream>
#include <string>

using namespace std;

// 给定一个链表和一个基数，重排链表使得小于基数的节点在左边，等于的在中间，大于的在右边
// 如    4-> 6-> 3-> 5-> 8-> 5-> 2 -> 5   , 基数 5
// 排序后 2-> 3-> 4-> 5-> 5-> 5-> 6 -> 8
// 
struct Node
{
	int value;
	Node* next;
	bool operator==(const Node& rhs) const
	{
		return this->value == rhs.value && this->next == rhs.next;
	}
};

Node* sort_base_on_num(Node* head)
{

}

void test_sort_base_on_num()
{
}