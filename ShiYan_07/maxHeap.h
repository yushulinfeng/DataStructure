#include "stdafx.h"
#include"binaryTree.cpp"
#include<stack>

class OutOfBounds{
public:
	OutOfBounds() { cout << "OutOfBounds!!!" << endl; }
};

class MustBeZero{
public:
	MustBeZero() { cout << "MustBeZero!!!" << endl; }
};

class NOMEM{
public:
	NOMEM() { cout << "NOMEM!!!" << endl; }
};

template <class T>
class maxHeap{
public:
	maxHeap():root(NULL){};
	~maxHeap(){};
	void Initialize(binaryTree<T> &tree);//基于普通树初始化
	maxHeap<T>& Insert(const T &x);
	maxHeap<T>& DeleteMax(T &x);
	void Output();
private:
	void Swap(binaryTreeNode<T> * b1, binaryTreeNode<T> *b2);
	void Sift(binaryTreeNode<T> * cur);
	binaryTreeNode<T> *root;
	binaryTree<T> *tree;
};

