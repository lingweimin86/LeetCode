#include <iostream>
#include <string>

using namespace std;

// ����һ�������һ����������������ʹ��С�ڻ����Ľڵ�����ߣ����ڵ����м䣬���ڵ����ұ�
// ��    4-> 6-> 3-> 5-> 8-> 5-> 2 -> 5   , ���� 5
// ����� 2-> 3-> 4-> 5-> 5-> 5-> 6 -> 8
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