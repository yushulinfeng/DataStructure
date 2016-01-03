#include "Node.h"

template <class T>
class Chain{
public :
	Chain();

	bool empty()const{ return listSize == 0; }
	int size()const{ return listSize; }

	void add(const T& theEle);//表头插入
	void insert(const T& theEle, int location);//指定位置插入
	void erase(int theIndex);//指定元素删除
	int indexOf(const T& theEle)const;//搜索元素
	void printchain();//输出
private :
	Node<T>* firstnode;
	int listSize;
	template<class T> friend class ListIterator;//友元类
};
