#include "stdafx.h"
#include "HashTable.cpp"
#include "ChainHashTable.h"
#include "TridiagonalMatrix.cpp"
#include "LowerMatrix.cpp"
#include "SparseMatrix.cpp"
              
#include <time.h>
#include <iostream>
using namespace std;

/* ������ */
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "-----------���ԽǾ���----------" << endl;
	TridiagonalMatrix<int> m01(5);
	for (int i = 1; i < 5; i++){//�������ݣ�����������Ϊ5��
		m01.Store(i, i , i);//Store����Ԫ��
		m01.Store(i, i , i + 1);
		m01.Store(i, i + 1, i);
	}
	m01.Store(1,5,5);
	cout << m01 << endl;
	cout << "Ԫ�أ�1,1��:  " << m01.Retrieve(1,1) << endl;//Retrieveȡ��Ԫ��

	 
	cout << "-----------�����Ǿ���-----------" << endl;
	LowerMatrix<int> m02(5);
	for (int i = 1; i <= 5; i++){//�������ݣ�������Ĭ�ϲ���Ϊ5��
		for (int j = 1; j <= i; j++){
			m02.Store(i+j,i,j);//Store����Ԫ��
		}   
	} 
	cout << m02 << endl;
	cout << "Ԫ�أ�1,1��:  " << m02.Retrieve(1, 1) << endl;//Retrieveȡ��Ԫ��


	cout << "-----------ϡ�����-----------" << endl;
	cout << "�������ݣ�" << endl;
	SparseMatrix<int> m03(5);
	for (int i = 0; i < 4; i++){//�������ݣ�������Ĭ�ϲ���Ϊ10��
		Term<int> term_temp; 
		term_temp.row = i; term_temp.col = i+1;
		term_temp.data = i + i + 1;      
		m03.Append(term_temp); 
	}
	cout << m03 << endl;
	cout << "ת�ã�" << endl;
	SparseMatrix<int> m04(5);
	m03.Transpose(m04);    
	cout << m04 << endl;
	cout << "��ӣ�" << endl;
	SparseMatrix<int> m05(5);
	m03.Add(m03,m05);//�˴����Լ����Լ�
	cout << m05 << endl;
	cout << "-----------END-----------" << endl << endl;

	      
	cout << "-----------����ɢ�н�����-----------" << endl;
	ChainHashTable<int, int> chain(37);
	for (int i = 0; i < 25; i++){
		int data = rand() % 1001;
		chain.Insert(data);    
	} 
	cout << chain << endl;


	cout << "-----------���Կ���Ѱַɢ��-----------" << endl;
	//����ɢ�б�  ��ʵ����������
	HashTable<int, int> hash(961);
	srand(time(0));
	for (int i = 0; i < 500; i++){
		int data = rand() % 1000+1;//1-1000��
		//��Ϊ������ʾ��0�ǿ�λ��ʼֵ�����Բ���0�������ײ鿴ʱ��⣩
		hash.Insert(data);   
	}
	cout << "�����ֵ����" << endl;
	cout << hash << endl;//��ӡ�ֵ��е�ȫ��Ԫ��
	

	int key, result, index, not_exit=1;
	while (not_exit){
		cout << "������Ҫ������������1~1000����";
		cin >> key;
		index = hash.Search(key, result);
		if (index != -1)
			cout << "���ڡ�������" << index << endl;
		else
			cout << "�����ڡ�" << endl;
		cout << "����������0����������ֵ������";
		cin >> not_exit;
	}


}
