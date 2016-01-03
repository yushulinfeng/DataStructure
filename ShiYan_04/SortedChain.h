#include "stdafx.h"

//链表结点
template<class E, class K>
class SortedChainNode
{
public:
	E data;
	SortedChainNode<E, K>*link;
};

//链表
template<class E, class K>
class SortedChain
{
public:
	SortedChain(){
		first = 0;
	}
	~SortedChain();
	bool IsEmpty()const{
		return first == 0;
	}
	int Length()const;
	bool Search(const K&k, E&e)const;
	SortedChain<E, K>&Delete(const K&k, E&e);
	SortedChain<E, K>&Insert(const E&e);
	SortedChain<E, K>&DistinctInsert(const E&e);
	void Output(ostream& out)const;
private:
	SortedChainNode<E, K>* first;
};