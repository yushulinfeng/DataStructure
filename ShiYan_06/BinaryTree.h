#include "stdafx.h"
#include "Queue.cpp"

//结点 
template<class T>
class TreeNode{
public:
	T data;
	TreeNode *lchild, *rchild;
};

//二叉树
template<class T>
class BinaryTree{
public:
	BinaryTree(){ CreateTestTree(); }
	void PreOrder(){ PreOrder(tree); }
	void InOrder(){ InOrder(tree); }
	void PostOrder(){ PostOrder(tree); }
	void LevelOrder(){ LevelOrder(tree); }
	int Depth(){ return Depth(tree); }
	int Count(){ int n = 0;	return Count(tree, n); }
	void SowPostOrder(char front[], char middle[]);//方便读取使用char[]
private:
	TreeNode<T>* tree;//树
	void CreateTestTree();//创建测试数
	TreeNode<T>* CreateMyTree();//输入创建树  
	void PreOrder(TreeNode<T>* tree);//前序
	void InOrder(TreeNode<T>* tree);//中序  
	void PostOrder(TreeNode<T>* tree);//后序  
	void LevelOrder(TreeNode<T>* tree);//层次遍历
	void Visit(TreeNode<T>* node);//访问某个节点
	int Depth(TreeNode<T>* tree);//深度
	int Count(TreeNode<T>* tree, int& count);//元素数目

	int pre_order[100];//求后序遍历准备,此处为方便解析使用int
	int mid_order[100];
	TreeNode<T>* SowPostOrder(int pre_l, int pre_r, int mid_l, int mid_r);//求后序遍历
};