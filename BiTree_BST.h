#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
#include <windows.h>

using namespace std;

struct TreeNode
{
	int value;
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


// 二叉搜索树(BST: binary search tree)   
//       子节点的值 <= 父节点的值 <=右子节点的值

// 二叉平衡树(AVL)
//	   仍是一棵二叉搜索树，只不过增加了平衡的要求, 对于树中任意结点，其左子树与右子树的高度之差的绝对值不大于1

// 二叉完全树
//     1)任一节点，有右无左，直接返回false
//     2)在遇到第一个只有左无右的节点，后面的节点必须都是叶节点(无左无右)

bool isBST(TreeNode* head, int& preValue)
{
	if (head == nullptr)
	{
		return true;
	}

	if (isBST(head->lChild, preValue) == false)
	{
		return false;
	}

	if (head->value <= preValue)
	{
		return false;
	}
	else
	{
		preValue = head->value;
	}

	return isBST(head->rChild, preValue);
}

struct TreeNodeInfo
{
	TreeNode* maxBSTNode;
	bool isBST;
	bool isLeave;
	int min;
	int max;
	int maxSize;
};

// 题目：找到一个二叉树中，最大的搜索二叉子树，返回该子树的节点个数
// TODO
// 如         3
//           / \
//          5   7
//         /\   /\
//        1  6  4 8
//        \    /\  \
//         2  2 10  9
// 最大子树是 5 1 6 2， 节点数是4
// A. 返回最大子树的节点数
// B. 返回最大子树的头结点

TreeNodeInfo findMaxSubBST_impl(TreeNode* head)
{
	if (head == nullptr)
	{
		return TreeNodeInfo{ nullptr, true, true, -1, -1, 0 };
	}

	TreeNodeInfo leftInfo = findMaxSubBST_impl(head->lChild);
	TreeNodeInfo rightInfo = findMaxSubBST_impl(head->rChild);

	//int min = min(head->value, leftInfo.min);
	//int max = max(head->value, rightInfo.max);
	int min = leftInfo.isLeave ? head->value : leftInfo.min;
	int max = rightInfo.isLeave ? head->value : rightInfo.max;

	if (leftInfo.isBST && rightInfo.isBST && 
		(leftInfo.isLeave || head->value >= leftInfo.max) && 
		(rightInfo.isLeave || head->value <= rightInfo.min))
	{
		return TreeNodeInfo{ head, true, false, min, max, (leftInfo.maxSize + rightInfo.maxSize + 1) };
	}
	else
	{
		TreeNode* maxBSTNode = leftInfo.maxBSTNode;
		int maxSize = leftInfo.maxSize;

		if (rightInfo.maxSize > leftInfo.maxSize)
		{
			maxBSTNode = rightInfo.maxBSTNode;
			maxSize = rightInfo.maxSize;
		}

		return TreeNodeInfo{ maxBSTNode, false, false, min, max, maxSize };
	}
}

TreeNode* findMaxSubBST(TreeNode* head)
{
	return findMaxSubBST_impl(head).maxBSTNode;
}

int minDepth_impl(TreeNode* root)
{
	if (root == nullptr)
	{
		return INT_MAX;
	}
	else if (root-> lChild == nullptr && root->rChild == nullptr)
	{
		return 1;
	}

	return min(minDepth_impl(root->lChild), minDepth_impl(root->rChild)) + 1;
}

int minDepth(TreeNode* root) {
	return minDepth_impl(root);
}

// 题目 求完全二叉树的节点个数，时间复杂度优于logN
// 找右子树最左节点，如果高度等于树的高度，则左子树是满的，节点数为2^(total height-level)-1+1，继续递归求右子树的节点个数
// 若高度不等，则右子树是满的且高度少1，节点数为2^(total height-level-1)-1+1，继续递归求左子树的节点个数
// TODO 

void test_BST()
{
	//             A
	//            / \
	//           B   C
	//          /   / \
	//         D   E   F
	  

	//TreeNode A{ 5 }, B{ 4 }, C{ 6 }, D{ 3 }, E{ 6 }, F{ 8 };
	//A.addChild(&B, &C);
	//B.addChild(&D, nullptr); C.addChild(&E, &F);


	//TreeNode A1{ 5 }, B1{ 4 }, C1{ 6 }, D1{ 3 }, E1{ 3 }, F1{ 8 };
	//A1.addChild(&B1, &C1);
	//B1.addChild(&D1, nullptr); C1.addChild(&E1, &F1);


	//bool res = isBST(&A);
	//cout << (res ? "it is a BST tree" : "is not a BST tree") << endl;

 //   res = isBST(&A1);
	//cout << (res ? "it is a BST tree" : "is not a BST tree") << endl;

//            3
//           / \
//          5   7
//         /\   /\
//        1  6  4 8
//        \    /\  \
//         2  2 10  9
//	TreeNode A1{ 3 }, B1{ 5 }, C1{ 7 }, D1{ 1 }, E1{ 6 }, F1{ 4 }, G1{ 8 }, H1{ 2 }, I1{ 2 }, J1{ 10 }, K1{ 9 };
//
//	A1.addChild(&B1, &C1);
//	B1.addChild(&D1, &E1);
//	C1.addChild(&F1, &G1);
//	D1.addChild(nullptr, &H1);
//	F1.addChild(&I1, &J1);
//	G1.addChild(nullptr, &K1);
//
//	cout << "the max sub BST node is: " << findMaxSubBST(&A1)->value << endl;


	TreeNode A1{ 1 }, B1{ 2 }, C1{ 3 };
	A1.addChild(&B1, nullptr);
	B1.addChild(&C1, nullptr);

	int preValue = -1;
	int ans = minDepth(&A1);

	return;
}