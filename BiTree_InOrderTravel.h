#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <unordered_map>

using namespace std;

struct TreeNode
{
	char value;
	TreeNode* lChild;
	TreeNode* rChild;

	void addChild(TreeNode* lchild, TreeNode* rchild)
	{
		if (lchild != nullptr)
			this->lChild = lchild;
		if (rchild != nullptr)
			this->rChild = rchild;
	}
};

struct TreeNodeInfo
{
	int distance;
	int depth;
};

// ������� ���ӵ�-�����ڵ�-�����ӵ�
vector<char> bitree_inorder_travel(TreeNode root)
{
	TreeNode* cur = &root;
	stack<TreeNode> myStack;
	vector<char> vec;

	while (cur != nullptr || !myStack.empty())
	{
		while (cur != nullptr)
		{
			myStack.push(*cur);
			cur = cur->lChild;
		}

		cur = &myStack.top();
		vec.push_back(cur->value);
		myStack.pop();
		cur = cur->rChild;
	}
	return vec;
}

// ǰ������� ���ڵ���ǰ   ���ڵ�-�����ӵ�-�����ӵ�
vector<char> bitree_preorder_travel(TreeNode root)
{
	TreeNode* cur = &root;
	stack<TreeNode> myStack;
	vector<char> vec;

	while (cur != nullptr || !myStack.empty())
	{
		while (cur != nullptr)
		{
			vec.push_back(cur->value); // 
			myStack.push(*cur);
			cur = cur->lChild;
		}

		cur = &myStack.top();
		// vec.push_back(cur->value);
		myStack.pop();
		cur = cur->rChild;
	}
	return vec;
}

// ����˼·�� ǰ��
//       1)��ջ�е���һ���ڵ㣬
//       2����ӡ�ڵ�
//       3���ѽڵ���ӽڵ�ѹ��ջ�����Һ��� 

//        ����
//       1�����ΰ����ӽڵ�ѹ��ջ
//       2�������ڵ�ʱ����ӡ���������ӽڵ��ظ�1���Ĳ���


//       ���� TODO
//       1����ջ�е���һ���ڵ�
//       2���ѽڵ�ѹ����һ��ջ��Stack 2)
//       3) �ѽڵ���ӽڵ�ѹ��ջ���������
//       4����stack 2�����γ�ջ����ӡ

vector<char> bitree_preorder_travel_2(TreeNode* root)
{
	TreeNode* cur = nullptr;
	stack<TreeNode*> myStack;
	vector<char> vec;
	myStack.push(root);

	while (!myStack.empty())
	{
		cur = myStack.top();
		vec.push_back(cur->value);
		myStack.pop();

		if (cur->rChild != nullptr)
		{
			myStack.push(cur->rChild);
		}
		if (cur->lChild != nullptr)
		{
			myStack.push(cur->lChild);
		}
	}
	
	// TODO
	return vec;
}

vector<char> bitree_inorder_travel_2(TreeNode* root)
{
	stack<TreeNode*> myStack;
	vector<char> vec;
	myStack.push(root); 

	TreeNode* cur = root->lChild;
	while (!myStack.empty() || cur != nullptr)
	{
		while (cur != nullptr)
		{
			myStack.push(cur);
			cur = cur->lChild;
		}

		cur = myStack.top();
		vec.push_back(cur->value);
		myStack.pop();

		cur = cur->rChild;
	}

	return vec;
}

// ����ݹ�汾
void bitree_inorder_travel_r(TreeNode* root, vector<char>* vec)
{
	if (root == nullptr)
	{
		return;
	}

	bitree_inorder_travel_r(root->lChild, vec);
	vec->push_back(root->value);
	bitree_inorder_travel_r(root->rChild, vec);
}

void bitree_preorder_travel_r(TreeNode* root, vector<char>* vec)
{
	if (root == nullptr)
	{
		return;
	}

	vec->push_back(root->value);
	bitree_preorder_travel_r(root->lChild, vec);
	bitree_preorder_travel_r(root->rChild, vec);
}
// ��������� ���ڵ��ں�  �����ӵ�-�����ӵ� -�����ڵ�
void bitree_postorder_travel_r(TreeNode* root, vector<char>* vec)
{
	if (root == nullptr)
	{
		return;
	}

	bitree_postorder_travel_r(root->lChild, vec);
	bitree_postorder_travel_r(root->rChild, vec);
	vec->push_back(root->value);
}

// ��α��� (������ȱ���
// �ö��н��
vector<char> bitree_widthorder_travel(TreeNode* root)
{
	queue<TreeNode*> myQueue;
	vector<char> vec;
	TreeNode* cur;

	myQueue.push(root);
	while (!myQueue.empty() )
	{
		cur = myQueue.front();
		myQueue.pop();
		vec.push_back(cur->value);

		if (cur->lChild != nullptr)
		{
			myQueue.push(cur->lChild);
		}
		if (cur->rChild != nullptr)
		{
			myQueue.push(cur->rChild);
		}
	}

	return vec;
}

// �ҵ��������Ŀ�� (��ÿ�������Ľڵ�����
int bitree_width(TreeNode* root)
{
	queue<TreeNode*> myQueue;
	unordered_map<TreeNode*, int> nodeMap;
	TreeNode* cur;
	int maxWidth = 0;
	int curLevel = 1;
	int curWidth = 0;

	myQueue.push(root);
	nodeMap.insert(make_pair(root, 1));
	while (!myQueue.empty())
	{
		cur = myQueue.front();
		myQueue.pop();
		int level = nodeMap.at(cur);
		if (level == curLevel)
		{
			curWidth++;
		}
		else
		{
			curLevel++;
			maxWidth = max(maxWidth, curWidth);
			curWidth = 1;
		}

		if (cur->lChild != nullptr)
		{
			myQueue.push(cur->lChild);
			nodeMap.insert(make_pair(cur->lChild, curLevel + 1));

		}
		if (cur->rChild != nullptr)
		{
			myQueue.push(cur->rChild);
			nodeMap.insert(make_pair(cur->rChild, curLevel + 1));
		}
	}

	return max(curWidth, maxWidth);
}

int bitree_depth(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	return max(bitree_depth(root->lChild), bitree_depth(root->rChild)) + 1;
}

TreeNodeInfo max_distance_impl(TreeNode* node)
{
	if (node == nullptr)
	{
		return TreeNodeInfo{ 0, 0 };
	}

	TreeNodeInfo leftInfo = max_distance_impl(node->lChild);
	TreeNodeInfo rightInfo = max_distance_impl(node->rChild);

	int maxDistance = std::max(leftInfo.distance, rightInfo.distance);
	int depthSum = leftInfo.depth + rightInfo.depth;
	maxDistance = std::max(maxDistance, depthSum);

	int depth = max(leftInfo.depth, rightInfo.depth) + 1;

	return TreeNodeInfo{ maxDistance, depth };
}

// ��һ���������������/ֱ��
// p1,p2,p3��ȡ���ֵ
// p1: ����������󳤶�(��������ǰ�㣩
// p2: ����������󳤶�(��������ǰ�㣩
// p3: �������߶�+�������߶�(������ǰ�㣩
int bitree_diameter(TreeNode* head)
{
	TreeNodeInfo node = max_distance_impl(head);
	return node.distance;
}

// ���������ڵ㣬�ҳ������Ĺ�ͬ��һ�����Ƚڵ�, �ݹ�
TreeNode* bitree_lowest_ancestor(TreeNode* root, TreeNode* n1, TreeNode* n2)
{
	if (root == nullptr || root == n1 || root == n2)
	{
		return root;
	}

	TreeNode* left = bitree_lowest_ancestor(root->lChild, n1, n2);
	TreeNode* right = bitree_lowest_ancestor(root->rChild, n1, n2);

	if (left == nullptr || right == nullptr)
	{
		return left == nullptr ? right : left;
	}

	return root;
}

// ���л�һ������ǰ���� _ ���ָ������#����սڵ�
string bitree_serialize(TreeNode* root)
{
	if (root == nullptr)
	{
		return "#_";
	}

	string text = string{ root->value } + "_";
	text += bitree_serialize(root->lChild);
	text += bitree_serialize(root->rChild);
	
	return text;
}

// �����л�һ������ǰ���� _ ���ָ������#����սڵ�
TreeNode* bitree_deserialize_impl(queue<char>* myQueue)
{
	char value = myQueue->front();
	myQueue->pop();
	if (value == '#')
	{
		return nullptr;
	}

	TreeNode* node = new TreeNode;
	node->value = value;
	node->lChild = bitree_deserialize_impl(myQueue);
	node->rChild = bitree_deserialize_impl(myQueue);
	return node;
}

TreeNode* bitree_deserialize(string text)
{
	stringstream ss(text);
	queue<char> myQueue;
	string value;
	while(getline(ss, value, '_'))
	{
		if (!value.empty())
		{
			myQueue.push(value[0]);
		}
	}
	return bitree_deserialize_impl(&myQueue);
}

void test_bitree_inorder_travel()
{
	//             A
	//            / \
	//           B   C
	//          /   / \
	//         D   E   F
	//        / \   \
	//       G   H   I
	//
	//

	TreeNode A{ 'A' }, B{ 'B' }, C{ 'C' }, D{ 'D' }, E{ 'E' }, F{ 'F' }, G{ 'G' }, H{ 'H' }, I{ 'I' };
	A.lChild = &B; A.rChild = &C;
	B.lChild = &D; C.lChild = &E; C.rChild = &F;
	D.lChild = &G; D.rChild = &H; E.rChild = &I; 
	//A.addChild(&B, &C);
	//B.addChild(&D, nullptr); C.addChild(&E, &F);
	//D.addChild(&G, &H); E.addChild(nullptr, &I);

	vector<char> vec; 
	// inorder
	bitree_inorder_travel_r(&A, &vec);

	cout << "in order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // G, D, H, B, A, E, I, C, F,
	}

	cout << endl;
	vec.clear();
	// in-order 2
	vec = bitree_inorder_travel_2(&A);

	cout << "in order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // G, D, H, B, A, E, I, C, F,
	}

	cout << endl;
	vec.clear();
	// pre-order
	bitree_preorder_travel_r(&A, &vec);

	cout << "pre order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // A, B, D, G, H, C, E, I, F
	}

	cout << endl;
	vec.clear();
	// pre-order 2
	vec = bitree_preorder_travel_2(&A);

	cout << "pre order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // A, B, D, G, H, C, E, I, F
	}

	cout << endl;
	vec.clear();
	//
	bitree_postorder_travel_r(&A, &vec);

	cout << "post order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // G, H, D, B, I, E, F, C, A,
	}

	cout << endl;
	//

	vec = bitree_widthorder_travel(&A);

	cout << "width order: ";
	for (auto c : vec)
	{
		cout << c << ", "; // A, B, C, D, E, F, H, I
	}

	cout << endl;
	vec.clear();
	//

	cout << "The width is " << to_string(bitree_width(&A)) << endl;
	cout << "The depth is " << to_string(bitree_depth(&A)) << endl;
	cout << "The distance is " << to_string(bitree_diameter(&A)) << endl;
	cout << "The lowest ancestor of G & E is " << bitree_lowest_ancestor(&A, &G, &E)->value << endl;
	cout << "The lowest ancestor of I & F is " << bitree_lowest_ancestor(&A, &I, &F)->value << endl;
	// serialize
	string serializeText = bitree_serialize(&A);
	cout << "The serialize is " << serializeText << endl; // A_B_D_G_#_#_H_#_#_#_C_E_#_I_#_#_F_#_#_
	// deserialize
	TreeNode* A1 = bitree_deserialize(serializeText);
	// show the tree
	vec = bitree_preorder_travel_2(A1);
	cout << "deserialize the tree, the pre-order is ";
	for (auto c : vec)
	{
		cout << c << ", "; // A, B, D, G, H, C, E, I, F
	}

	cout << endl;
}