#include "stdafx.h"
//#include<stack> //���д�����

/*ջ-������ʽ*/
template <class T>
class Stack{ 
public :
	Stack(){ top = 0; }
	~Stack();
	bool IsEmpty() const{ return top == 0; }
	bool IsFull() const;
	Stack<T>& Push(const T& x);
	Stack<T>& Pop();
	T Top() const;
	Stack<T>& Pop(T& x);//pop+top
private :
	Node<T> *top;//ָ��ջ��
};
