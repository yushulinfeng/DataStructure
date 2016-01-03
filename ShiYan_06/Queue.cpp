#include "stdafx.h"
#include "Queue.h"

template <class T>
Queue<T>::~Queue(){
	Node<T> *next;
	while (front){
		next = front->link;
		delete front;
		front = next;
	}
}

template <class T>
bool Queue<T>::IsFull() const{
	try{
		Node<T> *p = new Node<T>;
		delete p;
		return false;
	}
	catch (NOMEM e){
		return true;
	}
}

template <class T>
T Queue<T>::First() const{
	if (IsEmpty()) throw OutOfBounds();
	return front->data;
}

template <class T>
T Queue<T>::Last() const{
	if (IsEmpty()) throw OutOfBounds();
	return rear->data;
}

template <class T>
Queue<T>& Queue<T>::Push(const T& x){
	Node<T> *p = new Node<T>;
	p->data = x;
	p->link = 0;
	if (front) rear->link = p;
	else front = p;
	rear = p;
	return *this;
}

template <class T>
Queue<T>& Queue<T>::Pop(T& x){
	if (IsEmpty())throw OutOfBounds();
	x = front->data;
	Node<T> *p = front;
	front = front->link;
	delete p;
	return *this;
}

template <class T>
Queue<T>& Queue<T>::Pop(){
	if (IsEmpty())throw OutOfBounds();
	Node<T> *p = front;
	front = front->link;
	delete p;
	return *this;
}