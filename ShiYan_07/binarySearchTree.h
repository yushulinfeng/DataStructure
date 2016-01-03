#include "stdafx.h"

template <class T>
struct BinaryNode
{
	T				element;
	BinaryNode		*left;
	BinaryNode		*right;
	BinaryNode(const T& theElement,
		BinaryNode *lt,
		BinaryNode *rt) :
		element(theElement),
		left(lt),
		right(rt){}
};

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree(){ m_root = NULL; }
	~BinarySearchTree(){ makeEmpty(m_root); }
	const T& findMin() { return findMin(m_root)->element; }
	const T& findMax() { return findMax(m_root)->element; }
	bool contains(const T& x) { return contains(x, m_root); }
	void insert(const T& x){ insert(x, m_root); }
	void remove(const T& x){ return remove(x, m_root); }
	void printTreeInPrev(){printTreeInPrev(m_root);};
	void printTreeInMid(){printTreeInMid(m_root);};
	void printTreeInPost(){printTreeInPost(m_root);};
private:
	BinaryNode<T> *m_root;
	void insert(const T& x, BinaryNode<T>* &t);
	void remove(const T& x, BinaryNode<T>* &t);
	BinaryNode<T>* findMin(BinaryNode<T>* t) const;
	BinaryNode<T>* findMax(BinaryNode<T>* t) const;
	bool contains(const T& x, const BinaryNode<T>* t) const;
	void makeEmpty(BinaryNode<T>* &t);
	void printTreeInPrev(BinaryNode<T>* t) const;
	void printTreeInMid(BinaryNode<T>* t) const;
	void printTreeInPost(BinaryNode<T>* t) const;
};

template <class T>
bool BinarySearchTree<T>::contains(const T& x, const BinaryNode<T>* t) const
{
	if (!t)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (x > t->element)
		return contains(x, t->right);
	else
		return true;
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMin(BinaryNode<T>* t) const
{
	if (!t)
		return NULL;
	if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMax(BinaryNode<T>* t) const
{
	if (t != NULL)
	while (t->right != NULL)
		t = t->right;
	return t;
}

template <class T>
void BinarySearchTree<T>::insert(const T& x, BinaryNode<T>* &t)
{
	if (t == NULL)
		t = new BinaryNode<T>(x, NULL, NULL);
	else if (x < t->element)
		insert(x, t->left);
	else if (x > t->element)
		insert(x, t->right);
}

template <class T>
void BinarySearchTree<T>::remove(const T& x, BinaryNode<T>* &t)
{
	if (t == NULL)
		return;
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else {
		if (t->left != NULL &&
			t->right != NULL){//2
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}else{//1
			BinaryNode<T> *oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete oldNode;
		}
	}
}

template <class T>
void  BinarySearchTree<T>::makeEmpty(BinaryNode<T>* &t)
{
	if (t){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

template <class T>
void BinarySearchTree<T>::printTreeInPrev(BinaryNode<T>* t) const
{
	if (t){
		cout << t->element << " ";
		printTreeInPrev(t->left);
		printTreeInPrev(t->right);
	}
}
template <class T>
void BinarySearchTree<T>::printTreeInMid(BinaryNode<T>* t) const
{
	if (t){
		printTreeInMid(t->left);
		cout << t->element << " ";
		printTreeInMid(t->right);
	}
}
template <class T>
void BinarySearchTree<T>::printTreeInPost(BinaryNode<T>* t) const
{
	if (t){
		printTreeInPost(t->left);
		printTreeInPost(t->right);
		cout << t->element << " ";
	}
}




