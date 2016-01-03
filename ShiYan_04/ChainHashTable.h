#include "stdafx.h"
#include "SortedChain.cpp"

/*使用链表解决散列表溢出问题*/
template<class E, class K>
class ChainHashTable
{
public:
	ChainHashTable(int divisor = 11){
		D = divisor;
		ht = new SortedChain<E, K>[D];
	}
	~ChainHashTable(){ delete[]ht; }
	bool Search(const K& k, E& e)const{
		return ht[k%D].Search(k, e);
	}
	ChainHashTable<E, K> & Insert(const E& e){
		ht[e%D].DistinctInsert(e);//Distinct:不同的
		return *this;
	}
	ChainHashTable <E, K>& Delete(const K& k, E& e){
		ht[k%D].Delete(k, e);
		return *this;
	}
	void Output(ostream & out)const{
		for (int i = 0; i < D; i++){
				out << ht[i]<<"\n";//这样更直观
		}
	}
private:
	int D;//位置数
	SortedChain<E, K> *ht;//链表数组
};

//重载<<
template<class E, class K>
ostream& operator<<(ostream& out, ChainHashTable<E, K> &x)
{
	x.Output(out);
	return out;
}