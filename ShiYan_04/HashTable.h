#include "stdafx.h"

/*线性开型寻址的散列表的类*/
//E：元素，K：元素关键字。此处为了方便没有重载运算符，因此EK只能为数字类型。
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
	int hSearch(const K& k)const;//搜索
	int D;//散列函数的除数
	E *ht;//散列数组
	bool *empty0;//一维数组
};