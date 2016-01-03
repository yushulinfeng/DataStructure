#include "stdafx.h"
#include "SortedChain.h"

template<class E, class K>
SortedChain<E, K>::~SortedChain()
{
	SortedChainNode<E, K> *next;
	while (first)
	{
		next = first->link;
		delete first;
		first = next;
	}
}

template<class E, class K>
int SortedChain<E, K>::Length()const
{
	SortedChainNode<E, K> *current = first;
	int len = 0;
	while (current)
	{
		len++;
		current = current->link;
	}
	return len;
}

template <class E, class K>
bool SortedChain<E, K>::Search(const K&k, E&e)const
{
	SortedChainNode<E, K>*p = first;
	for (; p&&p->data<k;)
	{
		p = p->link;
	}
	if (p&&p->data == k)
	{
		e = p->data; return true;
	}
	return false;
}

template <class E, class K>
SortedChain<E, K>&SortedChain<E, K>::Insert(const E&e)
{
	SortedChainNode<E, K>*p = first, *tp = 0;
	for (; p&&p->data<e; tp = p, p = p->link);
	SortedChainNode<E, K>*q = new SortedChainNode<E, K>;
	q->data = e;
	q->link = p;
	if (tp)
	{
		tp->link = q;
	}
	else first = q;
	return *this;
}

template <class E, class K>
SortedChain<E, K>&SortedChain<E, K>::Delete(const K&k, E&e)
{
	SortedChainNode<E, K> *p = first, *tp = 0;
	for (; p&&p->data<k; tp = p, p = p->link);
	if (p&&p->data == k)
	{
		e = p->data;
		if (tp)
		{
			tp->link = p->link;
		}
		else first = p->link;
		delete p;
		return *this;
	}
	throw BadInput();
}

template <class E, class K>
SortedChain<E, K>&SortedChain<E, K>::DistinctInsert(const E&e)
{
	SortedChainNode<E, K>*p = first, *tp = 0;
	//for (; p&&p->data<e; tp = p, p = p->link)//Ԫ���ظ����˴�Ϊ�������ֱ�Ӻ��ԡ�
	//if (p&&p->data == e)
	//{
	//	throw BadInput();
	//}
	SortedChainNode<E, K>*q = new SortedChainNode<E, K>;
	q->data = e;
	q->link = p;
	if (tp)
	{
		tp->link = q;
	}
	else first = q;
	return *this;
}

//�������     
template<class E, class K>
void SortedChain<E, K>::Output(ostream& out)const{
	SortedChainNode<E, K>*current;
	if (!first)//�ձ�
		out << "0";
	for (current = first; current; current = current->link){
		out << current->data; 
		if (!current->link)//��β
			out << "";
		else//Ԫ�طָ���
			out << ",";
	}
}

//����<<
template<class E, class K>
ostream& operator<<(ostream& out, SortedChain<E, K> &x)
{
	x.Output(out);
	return out;
}