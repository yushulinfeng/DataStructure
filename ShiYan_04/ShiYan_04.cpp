#include "stdafx.h"
#include "HashTable.cpp"
#include "ChainHashTable.h"
#include "TridiagonalMatrix.cpp"
#include "LowerMatrix.cpp"
#include "SparseMatrix.cpp"
              
#include <time.h>
#include <iostream>
using namespace std;

/* 主方法 */
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "-----------三对角矩阵----------" << endl;
	TridiagonalMatrix<int> m01(5);
	for (int i = 1; i < 5; i++){//测试数据（构造器参数为5）
		m01.Store(i, i , i);//Store存入元素
		m01.Store(i, i , i + 1);
		m01.Store(i, i + 1, i);
	}
	m01.Store(1,5,5);
	cout << m01 << endl;
	cout << "元素（1,1）:  " << m01.Retrieve(1,1) << endl;//Retrieve取出元素

	 
	cout << "-----------下三角矩阵-----------" << endl;
	LowerMatrix<int> m02(5);
	for (int i = 1; i <= 5; i++){//测试数据（构造器默认参数为5）
		for (int j = 1; j <= i; j++){
			m02.Store(i+j,i,j);//Store存入元素
		}   
	} 
	cout << m02 << endl;
	cout << "元素（1,1）:  " << m02.Retrieve(1, 1) << endl;//Retrieve取出元素


	cout << "-----------稀疏矩阵-----------" << endl;
	cout << "测试数据：" << endl;
	SparseMatrix<int> m03(5);
	for (int i = 0; i < 4; i++){//测试数据（构造器默认参数为10）
		Term<int> term_temp; 
		term_temp.row = i; term_temp.col = i+1;
		term_temp.data = i + i + 1;      
		m03.Append(term_temp); 
	}
	cout << m03 << endl;
	cout << "转置：" << endl;
	SparseMatrix<int> m04(5);
	m03.Transpose(m04);    
	cout << m04 << endl;
	cout << "相加：" << endl;
	SparseMatrix<int> m05(5);
	m03.Add(m03,m05);//此处是自己加自己
	cout << m05 << endl;
	cout << "-----------END-----------" << endl << endl;

	      
	cout << "-----------链表散列解决溢出-----------" << endl;
	ChainHashTable<int, int> chain(37);
	for (int i = 0; i < 25; i++){
		int data = rand() % 1001;
		chain.Insert(data);    
	} 
	cout << chain << endl;


	cout << "-----------线性开形寻址散列-----------" << endl;
	//创建散列表  并实现搜索操作
	HashTable<int, int> hash(961);
	srand(time(0));
	for (int i = 0; i < 500; i++){
		int data = rand() % 1000+1;//1-1000。
		//（为方便显示，0是空位初始值。可以插入0，但容易查看时误解）
		hash.Insert(data);   
	}
	cout << "创建字典完成" << endl;
	cout << hash << endl;//打印字典中的全部元素
	

	int key, result, index, not_exit=1;
	while (not_exit){
		cout << "请输入要搜索的整数（1~1000）：";
		cin >> key;
		index = hash.Search(key, result);
		if (index != -1)
			cout << "存在。索引：" << index << endl;
		else
			cout << "不存在。" << endl;
		cout << "结束请输入0，输入其他值继续：";
		cin >> not_exit;
	}


}
