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
	bool isEmpty() const {//�ж����Ƿ�Ϊ��
		return root == NULL ? true : false;
	}
	bool isLeftChild(binaryTreeNode<T> * p){//�жϵ�ǰ�ڵ��Ƿ�Ϊ����
		return p == (p->getParent()->getLeftChild())? true : false;
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
