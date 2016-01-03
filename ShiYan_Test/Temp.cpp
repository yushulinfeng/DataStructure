#include "stdafx.h"
#include<stack>
#include<queue>
#include "string.h"
#include<iostream>
using namespace std;

//（最大堆）二叉树节点
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

//（最大堆）二叉树
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
		return p == (p->getParent()->getLeftChild()) ? true : false;
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
		cout << root->getData() << " ";
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
		if (root->getLeftChild() == NULL || root->getRightChild() == NULL){
			return root;
		}
		else{
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

//最大堆
template <class T>
class maxHeap{
public:
	maxHeap() :root(NULL){};
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

//堆排序
template <class T>
void HeapSort(T* arrays, int array_length){
	maxHeap<T> temp_heap;
	for (int i = 0; i < array_length; i++){
		temp_heap.Insert(arrays[i]);
	}
	int temp_int = 0;
	for (int i = 0; i < array_length; i++){
		temp_heap.DeleteMax(temp_int);
		cout << temp_int << " ";
	}
}

void testMaxHeap()
{
	//先构造一棵普通的完全二叉树
	binaryTreeNode<int> *t1, *t3, *t4, *t5, *t6;
	binaryTree<int> tree1(20);
	t1 = tree1.getRoot();
	tree1.insertLeftChild(t1, 12);
	tree1.insertRightChild(t1, 35);
	t3 = t1->getLeftChild();
	tree1.insertLeftChild(t3, 15);
	tree1.insertRightChild(t3, 10);
	t4 = t1->getRightChild();
	tree1.insertLeftChild(t4, 80);
	tree1.insertRightChild(t4, 30);
	t5 = t3->getLeftChild();
	tree1.insertLeftChild(t5, 17);
	tree1.insertRightChild(t5, 2);
	t6 = t3->getRightChild();
	tree1.insertLeftChild(t6, 1);
	cout << "普通二叉树（层次遍历）:" << endl;
	tree1.leverOrderTraverse(t1);
	cout << endl;

	maxHeap<int> heap;
	heap.Initialize(tree1);
	cout << "初始化为最大堆（层次遍历）:" << endl;
	heap.Output();
	cout << endl;

	int int_array[5] = { 5, 9, 8, 3, 1 };
	////若要使用键盘输入，把这些注释取消即可
	//int s;
	//cout << "请输入10个数：" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cin >> s;
	//	int_array[i] = s;
	//}
	cout << "原数组:" << endl;
	for (int i = 0; i < 5; i++)
		cout << int_array[i] << " ";
	cout << "\n堆排序:" << endl;
	HeapSort(int_array, 5);
	cout << endl;
}

//void main(){
//	testMaxHeap();
//}
