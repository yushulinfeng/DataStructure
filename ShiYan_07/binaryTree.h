#include "stdafx.h"

#include"binaryTreeNode.h"
#include<queue>

template <class T>
class binaryTree
{
public:
	binaryTree() : root(NULL){}
	binaryTree(const T value){
		root = new binaryTreeNode<T>(value);
	}
	virtual ~binaryTree();
	bool isEmpty() const {//判断树是否为空
		return root == NULL ? true : false;
	}
	bool isLeftChild(binaryTreeNode<T> * p){//判断当前节点是否为左孩子
		return p == (p->getParent()->getLeftChild())? true : false;
	}
	bool isRightChild(binaryTreeNode<T> * p){//判断当前节点是否为右孩子
		return p == (p->getParent()->getRightChild()) ? true : false;
	}
	binaryTreeNode<T> *getRoot(){//返回根节点
		return root;
	}
	binaryTreeNode<T> *leftChild(binaryTreeNode<T> *p){//返回当前节点的左孩子
		return p == NULL ? NULL : p->getLeftChild();
	}
	binaryTreeNode<T> *rightChild(binaryTreeNode<T> *p){//返回当前节点的右孩子
		return p == NULL ? NULL : p->getRightChild();
	}
	binaryTreeNode<T> *leftSibling(binaryTreeNode<T> *p){//返回当前节点的左兄弟
		binaryTreeNode<T> * parent = p->getParent();
		return parent->getLeftChild();
	}

	binaryTreeNode<T> *rightSibling(binaryTreeNode<T> *p){//返回当前节点的右兄弟
		binaryTreeNode<T> * parent = p->getParent();
		return p->getRightChild();
	}
	T retrieve(binaryTreeNode<T> *p) const {//返回当前节点的数据
		return p->getData();
	}
	void assign(binaryTreeNode<T> * p, const T value){//对当前节点数据进行重置
		p->setData(value);
	}
	void insertLeftChild(binaryTreeNode<T> * p, const T value);//在当前节点插入一个左孩子
	void insertLeftChild(binaryTreeNode<T> * p, binaryTreeNode<T> * leftChild);//重载在当前节点插如一个左孩子，该插入可以连接两棵树
	void insertRightChild(binaryTreeNode<T> * p, const T value);//在当前节点插入一个右孩子
	void insertRightChild(binaryTreeNode<T> * p, binaryTreeNode<T> * rightChild);//重载在当前节点插如一个右孩子，该插入可以连接两棵树
	void deleteRightChild(binaryTreeNode<T> *p){//删除右孩子
		destroy(p->getRightChild());
		p->setRightChild(NULL);
	}
	void deleteLeftChild(binaryTreeNode<T> *p){//删除左孩子
		destroy(p->getLeftChild());
		p->setLeftChild(NULL);
	}
	virtual void preOrderTraverse(binaryTreeNode<T> *root) const;//前序遍历
	virtual void inOrderTraverse(binaryTreeNode<T> *root) const;//中序遍历
	virtual void postOrderTraverse(binaryTreeNode<T> *root) const;//后序遍历
	virtual void leverOrderTraverse(binaryTreeNode<T> *root) const;//层次遍历
	binaryTreeNode<T> * getCompleteNextParent(binaryTreeNode<T> *root) const;//获取完全二叉树的下个插入点的父节点
	binaryTreeNode<T> * getCompleteLastElement(binaryTreeNode<T> *root) const;//获取完全二叉树的最后一个节点
private:
	void destroy(binaryTreeNode<T> *);//删除以当前节点为根的树
	binaryTreeNode<T> * root;
};
