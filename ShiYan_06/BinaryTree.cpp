#include "stdafx.h"
#include "BinaryTree.h"

template<class T>
void BinaryTree<T>::CreateTestTree()//创建测试树  1/2,3/4,5
{
	TreeNode<T>* node4 = new TreeNode<T>();
	node4->data = 4;
	node4->lchild = NULL;
	node4->rchild = NULL;
	TreeNode<T>* node5 = new TreeNode<T>();
	node5->data = 5;
	node5->lchild = NULL;
	node5->rchild = NULL;

	TreeNode<T>* node2 = new TreeNode<T>();
	node2->data = 2;
	node2->lchild = node4;
	node2->rchild = node5;
	TreeNode<T>* node3 = new TreeNode<T>();
	node3->data = 3;
	node3->lchild = NULL;
	node3->rchild = NULL;

	tree = new TreeNode<T>();
	tree->data = 1;
	tree->lchild = node2;
	tree->rchild = node3;
}

template<class T>
TreeNode<T>* BinaryTree<T>::CreateMyTree()//手动创建树  
{
	T p;//暂时用这个
	TreeNode<T>* tree;
	cin >> p;
	cout << p;
	if (p == 0)
		tree = NULL;
	else
	{
		tree = new TreeNode<T>();//为s结点开辟空间  
		tree->data = p;
		tree->lchild = CreateBiTree();
		tree->rchild = CreateBiTree();
	}
	return (tree);
}

template<class T>
void BinaryTree<T>::PreOrder(TreeNode<T>* tree)//前序
{
	if (tree != NULL)
	{
		Visit(tree);
		PreOrder(tree->lchild);
		PreOrder(tree->rchild);
	}
}

template<class T>
void BinaryTree<T>::InOrder(TreeNode<T>* tree)//中序  
{
	if (tree != NULL)
	{
		InOrder(tree->lchild);
		Visit(tree);
		InOrder(tree->rchild);
	}
}

template<class T>
void BinaryTree<T>::PostOrder(TreeNode<T>* tree)//后序  
{
	if (tree != NULL)
	{
		PostOrder(tree->lchild);
		PostOrder(tree->rchild);
		Visit(tree);
	}
}

template<class T>
void BinaryTree<T>::LevelOrder(TreeNode<T>* tree)//层次遍历  
{
	Queue<TreeNode<T>> Q;
	TreeNode<T> p;
	Q.Push(*tree);
	while (!Q.IsEmpty())
	{
		Q.Pop(p);
		Visit(&p);
		if (p.lchild != NULL)
			Q.Push(*(p.lchild));
		if (p.rchild != NULL)
			Q.Push(*(p.rchild));
	}
}

template<class T>
void BinaryTree<T>::Visit(TreeNode<T>* node)//访问
{
	cout << node->data << " ";
}

template<class T>
int BinaryTree<T>::Depth(TreeNode<T>* tree)//深度
{
	int num1, num2;
	if (tree == NULL)
		return(0);
	num1 = Depth(tree->lchild);
	num2 = Depth(tree->rchild);
	if (num1 > num2)
		return(num1 + 1);
	else
		return(num2 + 1);
}

template<class T>
int BinaryTree<T>::Count(TreeNode<T>* tree, int& count)//元素数目
{
	if (tree != NULL)//同前序
	{
		count++;
		Count(tree->lchild, count);
		Count(tree->rchild, count);
		return count;
	}
}

template<class T>
void BinaryTree<T>::SowPostOrder(char front[], char middle[]){
	for (int i = 0; i < 100; i++){
		if (front[i] == '\0')
			break;
		pre_order[i] = front[i] - 48;
	}
	for (int i = 0; i < 100; i++){
		if (middle[i] == '\0')
			break;
		mid_order[i] = middle[i] - 48;
	}
	int n = strlen(front);
	TreeNode<T>* show = SowPostOrder(0, n - 1, 0, n - 1);
	PostOrder(show);
}

template<class T>
TreeNode<T>* BinaryTree<T>::SowPostOrder(int pre_l, int pre_r, int mid_l, int mid_r)//求后序
{
	if (pre_r - pre_l < 0)
	{
		return NULL;
	}
	TreeNode<T> *root;
	root = new TreeNode<T>();
	root->data = pre_order[pre_l];
	if (pre_r == pre_l)
	{
		root->lchild = NULL;
		root->rchild = NULL;
		return root;
	}
	int index;
	for (index = mid_l; index <= mid_r; index++)
	{
		if (mid_order[index] == pre_order[pre_l])
			break;
	}
	root->lchild = SowPostOrder(pre_l + 1, pre_l + (index - mid_l), mid_l, index - 1);
	root->rchild = SowPostOrder(pre_l + (index - mid_l) + 1, pre_r, index + 1, mid_r);
	return root;
}
