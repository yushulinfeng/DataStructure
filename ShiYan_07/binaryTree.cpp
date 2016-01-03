#include "stdafx.h"
#include "binaryTree.h"

template <class T> 
binaryTree<T>:: ~binaryTree()
{
	destroy(root);
	root = NULL;
}

template <class T>
void binaryTree<T>::destroy(binaryTreeNode<T> *root)//用非递归实现销毁树
{
	queue< binaryTreeNode<T> * > q;
	if (NULL != root)
		q.push(root);
	while (!q.empty())
	{
		root = q.front();
		q.pop();
		if (root->getLeftChild())
			q.push(root->getLeftChild());
		if (root->getRightChild())
			q.push(root->getRightChild());
		delete root;
	}

}

template <class T>
void binaryTree<T>::insertLeftChild(binaryTreeNode<T> * p, const T value)
{
	binaryTreeNode<T> * add = new binaryTreeNode<T>(value);
	add->setLeftChild(p->getLeftChild());
	p->setLeftChild(add);
	add->setParent(p);

}

template <class T>
void binaryTree<T>::insertLeftChild(binaryTreeNode<T> * p, binaryTreeNode<T> * leftChild)
{
	p->setLeftChild(leftChild);
	leftChild->setParent(p);

}

template <class T>
void binaryTree<T>::insertRightChild(binaryTreeNode<T> * p, const T value)
{
	binaryTreeNode<T> * add = new binaryTreeNode<T>(value);
	add->setRightChild(p->getRightChild());
	p->setRightChild(add);
	add->setParent(p);

}

template <class T>
void binaryTree<T>::insertRightChild(binaryTreeNode<T> * p, binaryTreeNode<T> * rightChild)
{
	p->setRightChild(rightChild);
	rightChild->setParent(p);
}

template <class T>
void binaryTree<T>::preOrderTraverse(binaryTreeNode<T> *root) const// 用递归实现
{
	if (root != NULL){
		cout << root->getData();
		preOrderTraverse(root->getLeftChild());
		preOrderTraverse(root->getRightChild());

	}
}

template <class T>
void binaryTree<T>::inOrderTraverse(binaryTreeNode<T> *root) const
{
	if (root != NULL){
		inOrderTraverse(root->getLeftChild());
		cout << root->getData();
		inOrderTraverse(root->getRightChild());
	}
}

template <class T>
void binaryTree<T>::postOrderTraverse(binaryTreeNode<T> *root) const
{
	if (root != NULL){
		postOrderTraverse(root->getLeftChild());
		postOrderTraverse(root->getRightChild());
		cout << root->getData();
	}
}

template <class T>
void binaryTree<T>::leverOrderTraverse(binaryTreeNode<T> *root) const
{
	queue< binaryTreeNode<T> * > q;
	if (NULL != root)
		q.push(root);
	while (!q.empty()){
		root = q.front();
		q.pop();
		cout << root->getData()<<" ";
		if (root->getLeftChild())
			q.push(root->getLeftChild());
		if (root->getRightChild())
			q.push(root->getRightChild());
	}
}


template <class T>
binaryTreeNode<T> * binaryTree<T>::getCompleteNextParent(binaryTreeNode<T> *root) const
{
	queue< binaryTreeNode<T> * > q;
	if (NULL != root)
		q.push(root);
	while (!q.empty()){
		root = q.front();
		q.pop();
		if (root->getLeftChild()==NULL || root->getRightChild()==NULL){
			return root;
		}else{
			q.push(root->getLeftChild());
			q.push(root->getRightChild());
		}
	}
	return root;
}

template <class T>
binaryTreeNode<T> * binaryTree<T>::getCompleteLastElement(binaryTreeNode<T> *root) const
{
	queue< binaryTreeNode<T> * > q;
	if (NULL != root)
		q.push(root);
	while (!q.empty()){
		root = q.front();
		q.pop();
		if (root->getLeftChild())
			q.push(root->getLeftChild());
		if (root->getRightChild())
			q.push(root->getRightChild());
	}
	return root;
}