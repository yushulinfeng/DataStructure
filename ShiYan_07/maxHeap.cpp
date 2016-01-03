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
	//堆的根节点
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

//调整位置
template <class T>
void maxHeap<T>::Sift(binaryTreeNode<T> * cur)
{
	while (cur->getLeftChild()){//如果还没有到达叶子节点
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
	//为x寻找插入位置
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
	//i从新的叶结点开始，并沿着树慢慢上升
	while (new_value != root && (new_value->getData()) > (new_value->getParent()->getData())){
		//不能把x放到此处
		Swap(new_value, new_value->getParent());
		new_value = new_value->getParent();
	}
	return *this;
}

template <class T>
maxHeap<T> & maxHeap<T>::DeleteMax(T &x){
	//检查堆是否为空
	if (tree->isEmpty())
		throw OutOfBounds();
	if (root == NULL)
		return *this;
	//取出最大元素并放入x中
	x = root->getData();
	//终止条件
	if (root->getLeftChild() == NULL)
		return *this;
	//把最后一个元素提到根元素
	binaryTreeNode<int> *last = tree->getCompleteLastElement(root);
	root->setData(last->getData());
	if (tree->isLeftChild(last))
		tree->deleteLeftChild(last->getParent());
	else
		tree->deleteRightChild(last->getParent());
	//重排一次（因为只有根元素一个是不正确的）
	Sift(root);
	return *this;
}
