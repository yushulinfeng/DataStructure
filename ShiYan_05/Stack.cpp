#include "stdafx.h"
#include "Stack.h" 

template <class T>
Stack<T>::~Stack(){
	Node<T> *next;
	while (top){
		next = top->link;
		delete top;
		top = next;
	}
}

template <class T>
bool Stack<T>::IsFull() const{
	try{
		Node<T> *p = new Node<T>;
		delete p;
		return false;
	}catch (NOMEM e){
		return true;
	}
}

template <class T>
T Stack<T>::Top() const{
	if (IsEmpty()) throw OutOfBounds();
	return top->data;
}

template <class T>
Stack<T>& Stack<T>::Push(const T& x){
	Node<T> *p = new Node<T>;
	p->data = x;
	p->link = top;
	top = p;
	return *this;
}

template <class T>
Stack<T>& Stack<T>::Pop(T& x){
	if (IsEmpty())throw OutOfBounds();
	x = top->data;
	Node<T> *p = top;
	top = top->link;
	delete p;
	return *this;
}

template <class T>
Stack<T>& Stack<T>::Pop(){
	if (IsEmpty())throw OutOfBounds();
	Node<T> *p = top;
	top = top->link;
	delete p;
	return *this;
}

