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

// 中序遍历 左子点-》父节点-》右子点
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

// 前序遍历， 父节点在前   父节点-》左子点-》右子点
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

// 左神思路： 前序
//       1)从栈中弹出一个节点，
//       2）打印节点
//       3）把节点的子节点压入栈，先右后左 

//        中序
//       1）依次把左子节点压入栈
//       2）弹出节点时，打印，并对右子节点重复1）的操作


//       后序 TODO
//       1）从栈中弹出一个节点
//       2）把节点压到另一个栈（Stack 2)
//       3) 把节点的子节点压入栈，先左后右
//       4）从stack 2中依次出栈并打印

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

// 中序递归版本
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
// 后序遍历， 父节点在后  》左子点-》右子点 -》父节点
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

// 层次遍历 (宽度优先遍历
// 用队列解决
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

// 找到二叉树的宽度 (即每层中最大的节点数）
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

// 求一个二叉树的最长距离/直径
// p1,p2,p3中取最大值
// p1: 左子树有最大长度(不经过当前点）
// p2: 右子树有最大长度(不经过当前点）
// p3: 左子树高度+右子树高度(经过当前点）
int bitree_diameter(TreeNode* head)
{
	TreeNodeInfo node = max_distance_impl(head);
	return node.distance;
}

// 给出两个节点，找出他俩的共同第一个祖先节点, 递归
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

// 序列化一棵树，前序，以 _ 作分割符，以#代表空节点
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

// 反序列化一棵树，前序，以 _ 作分割符，以#代表空节点
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