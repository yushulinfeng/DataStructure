#include "stdafx.h"

/*���Կ���Ѱַ��ɢ�б����*/
//E��Ԫ�أ�K��Ԫ�عؼ��֡��˴�Ϊ�˷���û����������������EKֻ��Ϊ�������͡�
template<class E, class K>
class HashTable
{
public:
	HashTable(int divisor = 11);
	~HashTable(){ delete[]ht; delete[] empty0; }
	int Search(const K &k, E &e)const;
	HashTable<E, K>& Insert(const E &e);
	void Output(ostream &out)const;
private:
	int hSearch(const K& k)const;//����
	int D;//ɢ�к����ĳ���
	E *ht;//ɢ������
	bool *empty0;//һά����
};