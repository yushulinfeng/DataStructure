#include "stdafx.h"
#include "SortedChain.cpp"

/*ʹ��������ɢ�б��������*/
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
		ht[e%D].DistinctInsert(e);//Distinct:��ͬ��
		return *this;
	}
	ChainHashTable <E, K>& Delete(const K& k, E& e){
		ht[k%D].Delete(k, e);
		return *this;
	}
	void Output(ostream & out)const{
		for (int i = 0; i < D; i++){
				out << ht[i]<<"\n";//������ֱ��
		}
	}
private:
	int D;//λ����
	SortedChain<E, K> *ht;//��������
};

//����<<
template<class E, class K>
ostream& operator<<(ostream& out, ChainHashTable<E, K> &x)
{
	x.Output(out);
	return out;
}