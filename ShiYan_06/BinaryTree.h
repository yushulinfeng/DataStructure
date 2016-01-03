#include "stdafx.h"
#include "Queue.cpp"

//��� 
template<class T>
class TreeNode{
public:
	T data;
	TreeNode *lchild, *rchild;
};

//������
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
	void SowPostOrder(char front[], char middle[]);//�����ȡʹ��char[]
private:
	TreeNode<T>* tree;//��
	void CreateTestTree();//����������
	TreeNode<T>* CreateMyTree();//���봴����  
	void PreOrder(TreeNode<T>* tree);//ǰ��
	void InOrder(TreeNode<T>* tree);//����  
	void PostOrder(TreeNode<T>* tree);//����  
	void LevelOrder(TreeNode<T>* tree);//��α���
	void Visit(TreeNode<T>* node);//����ĳ���ڵ�
	int Depth(TreeNode<T>* tree);//���
	int Count(TreeNode<T>* tree, int& count);//Ԫ����Ŀ

	int pre_order[100];//��������׼��,�˴�Ϊ�������ʹ��int
	int mid_order[100];
	TreeNode<T>* SowPostOrder(int pre_l, int pre_r, int mid_l, int mid_r);//��������
};