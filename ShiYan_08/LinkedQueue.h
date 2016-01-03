#include "stdafx.h"

// 异常类
class BadInput
{
public:
	BadInput() { cout << "BadInput!!!" << endl; }
};
class OutOfBounds
{
public:
	OutOfBounds() { cout << "OutOfBounds!!!" << endl; }
};

//队列
template <class T>
class Node
{
public:
	Node() {}
	virtual ~Node() {}
	T data;
	Node<T> *link;
};

template<class T>
class LinkedQueue
{
public:
	LinkedQueue();
	virtual ~LinkedQueue();
	bool IsEmpty() const { return ((front) ? false : true); }
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
public:
	Node<T> *front;
	Node<T> *rear;
};

template <class T>
LinkedQueue<T>::LinkedQueue()
{
	front = rear = 0;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	Node<T> *next;
	while (front){
		next = front->link;
		delete front;
		front = next;
	}
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	Node<T> *p = new Node<T>;
	p->data = x;
	p->link = 0;
	if (front)
		rear->link = p;
	else front = p;
	rear = p;
	return *this;
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{
	if (IsEmpty()){
		return *this;
	}
	x = front->data;
	Node<T> *p = front;
	front = front->link;
	delete p;
	return *this;
}