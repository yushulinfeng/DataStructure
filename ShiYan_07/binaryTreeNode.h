#include "stdafx.h"

template <class T>
class binaryTreeNode
{
	T data;
	binaryTreeNode<T> * leftChild;
	binaryTreeNode<T> * rightChild;
	binaryTreeNode<T> * parent;
public:
	binaryTreeNode() : data(-1), leftChild(NULL), rightChild(NULL), parent(NULL){}
	binaryTreeNode(const T value) :data(value), leftChild(NULL), rightChild(NULL), parent(NULL){}
	~binaryTreeNode(){ }
	T & getData(){
		return data;
	}
	binaryTreeNode<T> * getLeftChild(){
		return leftChild;
	}
	binaryTreeNode<T> * getRightChild(){
		return rightChild;
	}
	binaryTreeNode<T> * getParent(){
		return parent;
	}
	void setData(T value){
		data = value;
	}
	void setLeftChild(binaryTreeNode<T> * newLeftChild){
		leftChild = newLeftChild;
	}
	void setRightChild(binaryTreeNode<T> * newRightChild){
		rightChild = newRightChild;
	}
	bool isRoot(){
		return this->getParent() == NULL ? true : false;
	}
	void setParent(binaryTreeNode<T> * newParent){
		parent = newParent;
	}
};
