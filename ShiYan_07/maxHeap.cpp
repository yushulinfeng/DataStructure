#include "stdafx.h"
#include "maxHeap.h"

template <class T>
void maxHeap<T>::Initialize(binaryTree<T> &binary_tree)
{
	root = binary_tree.getRoot();
	queue< binaryTreeNode<int> * > q;
	stack< binaryTreeNode<int> * > s;
	if (NULL != root)
		q.push(root);
	while (!q.empty()){
		root = q.front();
		if (root->getLeftChild() != NULL || root->getRightChild() != NULL)
			s.push(root);
		q.pop();
		if (root->getLeftChild())
			q.push(root->getLeftChild());
		if (root->getRightChild())
			q.push(root->getRightChild());
	}
	while (!s.empty()){
		binaryTreeNode<int> * temp = s.top();
		Sift(temp);
		s.pop();
	}
	//�ѵĸ��ڵ�
	root = binary_tree.getRoot();
	tree = &binary_tree;
}

template <class T>
void maxHeap<T>::Swap(binaryTreeNode<T> * b1, binaryTreeNode<T> *b2)
{
	int tep;
	tep = b1->getData();
	b1->setData(b2->getData());
	b2->setData(tep);
}

template <class T>
void maxHeap<T>::Output()
{
	tree->leverOrderTraverse(root);
}

//����λ��
template <class T>
void maxHeap<T>::Sift(binaryTreeNode<T> * cur)
{
	while (cur->getLeftChild()){//�����û�е���Ҷ�ӽڵ�
		if (cur->getData() < cur->getLeftChild()->getData()
			&& (cur->getRightChild() == NULL ||
			cur->getRightChild()->getData() < cur->getLeftChild()->getData())){
			Swap(cur, cur->getLeftChild());
			cur = cur->getLeftChild();
		}
		else if (cur->getRightChild() != NULL&&cur->getData() < cur->getRightChild()->getData()
			&& cur->getLeftChild()->getData() < cur->getRightChild()->getData()){
			Swap(cur, cur->getRightChild());
			cur = cur->getRightChild();
		}
		else{
			return;
		}
	}
}

template <class T>
maxHeap<T> & maxHeap<T>::Insert(const T &x){
	//ΪxѰ�Ҳ���λ��
	binaryTreeNode<int> *new_value = new binaryTreeNode<int>(x);
	if (root == NULL || root->getData() == -1){
		root = new_value;
		tree = new binaryTree<int>(x);
		return *this;
	}
	binaryTreeNode<int> *last_parent = tree->getCompleteNextParent(root);
	if (last_parent->getLeftChild() == NULL)
		last_parent->setLeftChild(new_value);
	else
		last_parent->setRightChild(new_value);
	new_value->setParent(last_parent);
	//i���µ�Ҷ��㿪ʼ������������������
	while (new_value != root && (new_value->getData()) > (new_value->getParent()->getData())){
		//���ܰ�x�ŵ��˴�
		Swap(new_value, new_value->getParent());
		new_value = new_value->getParent();
	}
	return *this;
}

template <class T>
maxHeap<T> & maxHeap<T>::DeleteMax(T &x){
	//�����Ƿ�Ϊ��
	if (tree->isEmpty())
		throw OutOfBounds();
	if (root == NULL)
		return *this;
	//ȡ�����Ԫ�ز�����x��
	x = root->getData();
	//��ֹ����
	if (root->getLeftChild() == NULL)
		return *this;
	//�����һ��Ԫ���ᵽ��Ԫ��
	binaryTreeNode<int> *last = tree->getCompleteLastElement(root);
	root->setData(last->getData());
	if (tree->isLeftChild(last))
		tree->deleteLeftChild(last->getParent());
	else
		tree->deleteRightChild(last->getParent());
	//����һ�Σ���Ϊֻ�и�Ԫ��һ���ǲ���ȷ�ģ�
	Sift(root);
	return *this;
}
