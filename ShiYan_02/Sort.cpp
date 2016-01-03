#include "stdafx.h"

#include "Sort.h"
#include <iostream> 
using namespace std;

template<class T>
void Sort<T>::Swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
};

template<class T>
int Sort<T>::Max(T a[], int n)
{
	T max = 0; int position=0;
	for (int i = 0; i<n; i++)
	{
		if (max<a[i])
		{
			max = a[i];
			position = i;
		}
	}
	return position;
}

template<class T>
int Sort<T>::Partition(T a[], int first, int last)
{
	T x = a[last];
	int i = first - 1; 
	int j;
	for (j = first; j <= last - 1; j++)
	{// select
		if (a[j] <= x)
		{
			i = i + 1;
			Swap(a[i], a[j]);
		}
	}
	Swap(a[i + 1], a[last]);
	return i + 1;
};

template<class T>
void Sort<T>::Merge(T a[], int first, int middle, int last)
{
	int ln = middle - first + 1; 
	int rn = last - middle; 
	T max = a[Max(a, last + 1)];
	T* L;
	T* R;
	L = new T[ln];
	R = new T[rn];
	for (int i = 0; i<ln; i++)
		L[i] = a[first + i];
	for (int j = 0; j<rn; j++)
		R[j] = a[middle + j + 1];
	L[ln] = max + 1; 
	R[rn] = max + 1;
	int i = 0, j = 0;
	for (int k = first; k <= last; k++)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else{
			a[k] = R[j];
			j++;
		}
	}
};

//ð������
template<class T>
void Sort<T>::BubbleSort(T a[], int n){
	for (int i = 1; i < n; i++){//n-1 ci
		for (int j = 0; j<n - i; j++){//not sort finished
			if (a[j]>a[j + 1]){//max
				Swap(a[j], a[j + 1]);
			}
		}
	}
}

//ѡ������
template<class T>
void Sort<T>::SelectionSort(T a[],int n){
	for (int i = 0; i < n; i++){//start
		T min = a[i];
		int position = i;
		for (int j = i + 1; j < n; j++){//min 
			if (min>a[j]){
				min = a[j];
				position = j;
			}
		}	
		if (i!=position)
		Swap(a[i],a[position]);
	}
};

//�������� 
template<class T>
void Sort<T>::InsertionSort(T a[], int n){
	int j;
	for (int i = 1; i<n; i++){
		T t = a[i];
		for (j = i - 1; j >= 0 && t<a[j]; j--){
			a[j + 1] = a[j];
		}
		a[j + 1] = t;
	}
};

//�������� 
template<class T>
void Sort<T>::QuickSort(T a[], int first, int last)
{
	if (first<last)
	{
		int q = Partition(a, first, last);
		QuickSort(a, first, q - 1);
		QuickSort(a, q + 1, last);
	}
};

//�ϲ����� 
template<class T>
void Sort<T>::MergeSort(T a[], int first, int last)
{
	if (first<last)
	{
		int middle = (first + last) / 2;
		MergeSort(a, first, middle);
		MergeSort(a, middle + 1, last);
		Merge(a, first, middle, last);
	}
};

// �������� 
template<class T>
void Sort<T>::RadixSort(T a[], int n, int d)//������������dΪ��ߵ�λ�� 
{
	T* b;//���ÿ�ΰ�ĳһλ�źú������ 
	b = new T[n];
	for (int m = 0; m<d; m++)
	{//wen
		T k = 10;//���е�����󲻳���10����10Ϊ������ 
		T* c;//���Ԫ�ظ���
		c = new T[k];
		int x = pow(10, m);//λȨ 
		for (int i = 0; i <= k; i++)
			c[i] = 0;//��ʼ�� 
		for (int j = 0; j<n; j++)
			c[(a[j] / x) % 10]++;//C[i]��������i��Ԫ�ظ��� 
		for (int i = 1; i <= k; i++)
			c[i] += c[i - 1];//C[i]������С�ڻ����i��Ԫ�ظ��� 
		for (int j = n - 1; j >= 0; j--)
		{//1st
			b[c[(a[j] / x) % 10] - 1] = a[j];//b�������õ����� 
			c[(a[j] / x) % 10]--;//������һ 
		}
		for (int i = 0; i<n; i++)
			a[i] = b[i];//ÿ��ĳλ�źú��ٸ�ֵ��a�� 
	}
}
