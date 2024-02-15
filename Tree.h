#include <stdio.h>
#include <stdlib.h>

// 定时器  - 管理结构 用 二叉树
// 数据库/硬盘/磁道/扇区 - B+树
// 红黑树


typedef struct tree_s
{
	struct tree_s* left;
	struct tree_s* right;

	int d;
} tree_t;

void tree_insert(tree_t** proot, tree_t* node)
{
	while (*proot)
	{
		if (node->d < (*proot)->d)
		{
			proot = &(*proot)->left;
		}
		else {
			proot = &(*proot)->right;
		}
	}

	*proot = node;
}

void tree_insert_r(tree_t** proot, tree_t* node)
{
	if (*proot == NULL)
	{
		*proot = node;
		return;
	}

	if (node->d < (*proot)->d)
	{
		tree_insert_r(&(*proot)->left, node);
	}
	else {
		tree_insert_r(&(*proot)->right, node);
	}
}

void tree_del(tree_t** proot, int d)
{
	while (*proot)
	{
		tree_t* cur = *proot;

		if (d < (*proot)->d)
		{
			proot = &(*proot)->left;
		}
		else if (d > (*proot)->d) {
			proot = &(*proot)->right;
		}
		else // d == (*proot)->d
		{
			*proot = cur->left;
			if (cur->right)
			{
				tree_insert(proot, cur->right);
			}

			free(cur);
			cur = NULL;
			break;
		}
	}


}

void tree_print(tree_t* root)
{
	if (!root)
		return;

	tree_print(root->left);
	printf("%d\n", root->d);
	tree_print(root->right);
}

void test_tree()
{
	tree_t* root = NULL;
	tree_t* t;
	int i;

	for (int i = 5; i > 0; i -= 2)
	{
		t = (tree_t*)calloc(1, sizeof(tree_t));
		t->d = i;
		tree_insert(&root, t);
	}

	tree_print(root);

	printf("*********\n");

	for (int i = 0; i < 10; i += 2)
	{
		t = (tree_t*)calloc(1, sizeof(tree_t));
		t->d = i;
		tree_insert_r(&root, t);
	}

	tree_print(root);
	printf("*********\n");

	tree_del(&root, 0);
	tree_del(&root, 5);

	tree_print(root);
}
