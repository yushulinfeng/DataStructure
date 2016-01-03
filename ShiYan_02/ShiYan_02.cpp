#include "stdafx.h"

#include "Sort.cpp"

#include <iostream> 
using namespace std;

template<class T>//输出数组
void Output(T a[], int n, string name = ""){
	cout << name.c_str();
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
};

int* GetIntArray(){//获取一个测试的int数组
	int *a = new int[8];
	a[0] = 5;
	a[1] = 1;
	a[2] = 9;
	a[3] = 3;
	a[4] = 7;
	a[5] = 4;
	a[6] = 8;
	a[7] = 0;
	Output(a, 8, "原始数组：");
	//int a[8]={ 5, 1, 9, 3, 7, 4, 8, 0 };
	return a;
}

//主入口方法
int _tmain(int argc, _TCHAR* argv[])
{
	int* a;
	Sort<int> s;

	a = GetIntArray();
	s.BubbleSort(a, 8);
	Output(a, 8, "冒泡排序：");
	cout << endl;

	a = GetIntArray(); 
	s.SelectionSort(a, 8);
	Output(a, 8, "选择排序：");
	cout << endl;

	a = GetIntArray();
	s.InsertionSort(a, 8);
	Output(a, 8, "插入排序：");
	cout << endl; 

	a = GetIntArray();  
	s.QuickSort(a, 0, 7);  
	Output(a, 8, "快速排序："); 
	cout << endl; 

	a = GetIntArray();
	s.MergeSort(a, 0, 7);
	Output(a, 8, "合并排序：");
	cout << endl;

	a = GetIntArray();
	s.RadixSort(a, 8, 1);
	Output(a, 8, "基数排序：");
	cout << endl;
	   
	system("pause");
	return 0;
}