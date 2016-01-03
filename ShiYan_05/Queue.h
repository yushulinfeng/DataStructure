#include "stdafx.h"

/*��-������ʽ*/
template <class T>
class Queue{
public :
	Queue(){ front = rear = 0; }
	~Queue();
	bool IsEmpty() const{ return (front) ? false : true; }
	bool IsFull() const;
	T First() const;
	T Last() const;
	Queue<T>& Push(const T& x);
	Queue<T>& Pop();
	Queue<T>& Pop(T& x);//first+pop
private :
	Node<T> *front;//��ͷ
	Node<T> *rear;//��β
};