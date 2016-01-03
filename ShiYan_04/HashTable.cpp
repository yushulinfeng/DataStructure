#include "stdafx.h"
#include "HashTable.h"

//HashTable 的构造方法
template<class E, class K>
HashTable<E, K>::HashTable(int divisor)
{
	D = divisor;
	//分配散列数组
	ht = new E[D];
	for (int i = 0; i < D; i++)
		ht[i] = 0;
	empty0 = new bool[D];
	//将所有桶置空
	for (int i = 0; i < D; i++)
		empty0[i] = true;
}

//实现hSearch方法
template<class E, class K>
int HashTable<E, K>::hSearch(const K& k)const
{
	int i = k % D;//起始桶(override%)
	//从起始桶开始，在不返回起始桶的情况下遍历所有桶
	int j = i;
	do{
		if (empty0[j] || ht[j] == k)//空桶或找到(override==)
			return j;
		j = (j + 1) % D;
	} while (j != i);
	return j;//桶已满
}

//实现Search方法-根据关键字k查找元素，找到存入e
template<class E, class K>
int HashTable<E, K>::Search(const K &k, E &e)const
{
	int b = hSearch(k);
	if (empty0[b] || ht[b] != k)
		return -1;//找不到，返回-1
	e = ht[b];
	return b;//找到了就返回索引值
}

//实现Insert方法
template<class E, class K>
HashTable<E, K> & HashTable<E, K>::Insert(const E& e)
{
	K k = e;//抽取key值(override=)
	int b = hSearch(k);
	//检查是否能完成插入
	if (empty0[b]){
		empty0[b] = false;
		ht[b] = e;
		return *this;
	}	
	//不能插入，检查是否有重复值或表满
	if (ht[b] == k){//有重复
		//throw BadInput();//此处为方便测试有重复值直接跳过。（随机数不免重复）
	}else{//表满
		throw NOMEM();
	}
	return *this;
}

//实现Output方法
template<class E, class K>
void HashTable<E, K>::Output(ostream & out)const
{
	for (int i = 0; i < D; i++)
		out << ht[i] << "\t";
}

//重载<<
template<class E, class K>
ostream& operator<<(ostream& out, HashTable<E, K> &x)
{
	x.Output(out);
	return out;
}