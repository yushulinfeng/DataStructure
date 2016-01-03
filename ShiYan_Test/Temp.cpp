#include "stdafx.h"
#include<stack>
#include<queue>
#include "string.h"
#include<iostream>
using namespace std;

//�����ѣ��������ڵ�
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

//�����ѣ�������
template <class T>
class binaryTree
{
public:
	binaryTree() : root(NULL){}
	binaryTree(const T value){
		root = new binaryTreeNode<T>(value);
	}
	virtual ~binaryTree();
	bool isEmpty() const {//�ж����Ƿ�Ϊ��
		return root == NULL ? true : false;
	}
	bool isLeftChild(binaryTreeNode<T> * p){//�жϵ�ǰ�ڵ��Ƿ�Ϊ����
		return p == (p->getParent()->getLeftChild()) ? true : false;
	}
	bool isRightChild(binaryTreeNode<T> * p){//�жϵ�ǰ�ڵ��Ƿ�Ϊ�Һ���
		return p == (p->getParent()->getRightChild()) ? true : false;
	}
	binaryTreeNode<T> *getRoot(){//���ظ��ڵ�
		return root;
	}
	binaryTreeNode<T> *leftChild(binaryTreeNode<T> *p){//���ص�ǰ�ڵ������
		return p == NULL ? NULL : p->getLeftChild();
	}
	binaryTreeNode<T> *rightChild(binaryTreeNode<T> *p){//���ص�ǰ�ڵ���Һ���
		return p == NULL ? NULL : p->getRightChild();
	}
	binaryTreeNode<T> *leftSibling(binaryTreeNode<T> *p){//���ص�ǰ�ڵ�����ֵ�
		binaryTreeNode<T> * parent = p->getParent();
		return parent->getLeftChild();
	}

	binaryTreeNode<T> *rightSibling(binaryTreeNode<T> *p){//���ص�ǰ�ڵ�����ֵ�
		binaryTreeNode<T> * parent = p->getParent();
		return p->getRightChild();
	}
	T retrieve(binaryTreeNode<T> *p) const {//���ص�ǰ�ڵ������
		return p->getData();
	}
	void assign(binaryTreeNode<T> * p, const T value){//�Ե�ǰ�ڵ����ݽ�������
		p->setData(value);
	}
	void insertLeftChild(binaryTreeNode<T> * p, const T value);//�ڵ�ǰ�ڵ����һ������
	void insertLeftChild(binaryTreeNode<T> * p, binaryTreeNode<T> * leftChild);//�����ڵ�ǰ�ڵ����һ�����ӣ��ò����������������
	void insertRightChild(binaryTreeNode<T> * p, const T value);//�ڵ�ǰ�ڵ����һ���Һ���
	void insertRightChild(binaryTreeNode<T> * p, binaryTreeNode<T> * rightChild);//�����ڵ�ǰ�ڵ����һ���Һ��ӣ��ò����������������
	void deleteRightChild(binaryTreeNode<T> *p){//ɾ���Һ���
		destroy(p->getRightChild());
		p->setRightChild(NULL);
	}
	void deleteLeftChild(binaryTreeNode<T> *p){//ɾ������
		destroy(p->getLeftChild());
		p->setLeftChild(NULL);
	}
	virtual void preOrderTraverse(binaryTreeNode<T> *root) const;//ǰ�����
	virtual void inOrderTraverse(binaryTreeNode<T> *root) const;//�������
	virtual void postOrderTraverse(binaryTreeNode<T> *root) const;//�������
	virtual void leverOrderTraverse(binaryTreeNode<T> *root) const;//��α���
	binaryTreeNode<T> * getCompleteNextParent(binaryTreeNode<T> *root) const;//��ȡ��ȫ���������¸������ĸ��ڵ�
	binaryTreeNode<T> * getCompleteLastElement(binaryTreeNode<T> *root) const;//��ȡ��ȫ�����������һ���ڵ�
private:
	void destroy(binaryTreeNode<T> *);//ɾ���Ե�ǰ�ڵ�Ϊ������
	binaryTreeNode<T> * root;
};


template <class T>
binaryTree<T>:: ~binaryTree()
{
	destroy(root);
	root = NULL;
}

template <class T>
void binaryTree<T>::destroy(binaryTreeNode<T> *root)//�÷ǵݹ�ʵ��������
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
void binaryTree<T>::preOrderTraverse(binaryTreeNode<T> *root) const// �õݹ�ʵ��
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

//����
template <class T>
class maxHeap{
public:
	maxHeap() :root(NULL){};
	~maxHeap(){};
	void Initialize(binaryTree<T> &tree);//������ͨ����ʼ��
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

//������
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
	//�ȹ���һ����ͨ����ȫ������
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
	cout << "��ͨ����������α�����:" << endl;
	tree1.leverOrderTraverse(t1);
	cout << endl;

	maxHeap<int> heap;
	heap.Initialize(tree1);
	cout << "��ʼ��Ϊ���ѣ���α�����:" << endl;
	heap.Output();
	cout << endl;

	int int_array[5] = { 5, 9, 8, 3, 1 };
	////��Ҫʹ�ü������룬����Щע��ȡ������
	//int s;
	//cout << "������10������" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cin >> s;
	//	int_array[i] = s;
	//}
	cout << "ԭ����:" << endl;
	for (int i = 0; i < 5; i++)
		cout << int_array[i] << " ";
	cout << "\n������:" << endl;
	HeapSort(int_array, 5);
	cout << endl;
}

//void main(){
//	testMaxHeap();
//}
