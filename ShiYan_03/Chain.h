#include "Node.h"

template <class T>
class Chain{
public :
	Chain();

	bool empty()const{ return listSize == 0; }
	int size()const{ return listSize; }

	void add(const T& theEle);//��ͷ����
	void insert(const T& theEle, int location);//ָ��λ�ò���
	void erase(int theIndex);//ָ��Ԫ��ɾ��
	int indexOf(const T& theEle)const;//����Ԫ��
	void printchain();//���
private :
	Node<T>* firstnode;
	int listSize;
	template<class T> friend class ListIterator;//��Ԫ��
};
