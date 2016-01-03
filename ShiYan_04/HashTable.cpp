#include "stdafx.h"
#include "HashTable.h"

//HashTable �Ĺ��췽��
template<class E, class K>
HashTable<E, K>::HashTable(int divisor)
{
	D = divisor;
	//����ɢ������
	ht = new E[D];
	for (int i = 0; i < D; i++)
		ht[i] = 0;
	empty0 = new bool[D];
	//������Ͱ�ÿ�
	for (int i = 0; i < D; i++)
		empty0[i] = true;
}

//ʵ��hSearch����
template<class E, class K>
int HashTable<E, K>::hSearch(const K& k)const
{
	int i = k % D;//��ʼͰ(override%)
	//����ʼͰ��ʼ���ڲ�������ʼͰ������±�������Ͱ
	int j = i;
	do{
		if (empty0[j] || ht[j] == k)//��Ͱ���ҵ�(override==)
			return j;
		j = (j + 1) % D;
	} while (j != i);
	return j;//Ͱ����
}

//ʵ��Search����-���ݹؼ���k����Ԫ�أ��ҵ�����e
template<class E, class K>
int HashTable<E, K>::Search(const K &k, E &e)const
{
	int b = hSearch(k);
	if (empty0[b] || ht[b] != k)
		return -1;//�Ҳ���������-1
	e = ht[b];
	return b;//�ҵ��˾ͷ�������ֵ
}

//ʵ��Insert����
template<class E, class K>
HashTable<E, K> & HashTable<E, K>::Insert(const E& e)
{
	K k = e;//��ȡkeyֵ(override=)
	int b = hSearch(k);
	//����Ƿ�����ɲ���
	if (empty0[b]){
		empty0[b] = false;
		ht[b] = e;
		return *this;
	}	
	//���ܲ��룬����Ƿ����ظ�ֵ�����
	if (ht[b] == k){//���ظ�
		//throw BadInput();//�˴�Ϊ����������ظ�ֱֵ��������������������ظ���
	}else{//����
		throw NOMEM();
	}
	return *this;
}

//ʵ��Output����
template<class E, class K>
void HashTable<E, K>::Output(ostream & out)const
{
	for (int i = 0; i < D; i++)
		out << ht[i] << "\t";
}

//����<<
template<class E, class K>
ostream& operator<<(ostream& out, HashTable<E, K> &x)
{
	x.Output(out);
	return out;
}