#include "Chain.h"

#include <iostream>
using namespace std;

template<class T>
Chain<T>::Chain(){
	firstnode = NULL;
	listSize = 0;
}

template<class T>
int Chain<T>::indexOf(const T& theEle) const{
	Node<T> *current = firstnode;
	int index = 0;
	while (current != NULL && current->data != theEle){
		current = current->next;
		index++;
	}
	if (current == NULL) return -1;//not find
	return index;
}

template<class T>
void Chain<T> ::erase(int data){
	int index = indexOf(data);
	Node<T>* del = NULL;
	if (index == -1){//not find
		cout << "没找到可删除的元素" << endl;
	}else if (index == 0)	{//head
		del = firstnode;
		firstnode = firstnode->next;
		listSize--;
	}else{//normal
		Node<T>* p = firstnode;
		for (int i = 0; i < index - 1; i++){
			p = p->next;
		}
		del = p->next;
		p->next = p->next->next;//jump
		listSize--;
	}
	delete del;
}

template<class T>
void Chain<T>::add(const T& theEle)
{
	firstnode = new Node<T>(theEle, firstnode);
	listSize++;
}

template<class T>
void Chain<T>::insert(const T& theEle, int location){
	if (location <= listSize&&location >= 0){
		Node<T>* insertnode = new Node<T>(theEle, NULL);
		Node<T>* p = firstnode;
		if (firstnode == NULL)//head
			firstnode = new Node<T>(theEle, firstnode);
		else{
			if (location == 0){//null
				firstnode = new Node<T>(theEle, firstnode);
			}else{//normal
				for (int i = 0; i < location - 1; i++){
					p = p->next;
				}
				//not_over
				insertnode->next = p->next;//it->
				p->next = insertnode;//->it
			}
		}
		listSize++;
	}else{
		cout << "输入数字越界" << endl;
	}
}

template<class T>
void Chain<T>::printchain(){
	Node<T> *cur = firstnode;
	for (int i = 0; i < listSize; i++){
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}
