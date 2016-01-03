#include "stdafx.h"

template<class T>
class Sort {
private:
	void Swap(T& a, T& b);//��������Ԫ�� 
	int Max(T a[], int n);//�������ֵ����λ�� 
	int Partition(T a[], int first, int last);//����(�����һ����ΪKEY,����������λ��) 
	void Merge(T a[], int first, int middle, int last);//�ϲ������������� 
public:
	void BubbleSort(T a[], int n);//ð������ 
	void SelectionSort(T a[], int n);//ѡ������ 
	void InsertionSort(T a[], int n);//�������� 
	void QuickSort(T a[], int first, int last);//�������� 
	void MergeSort(T a[], int first, int last);//�ϲ����� 
	void RadixSort(T a[], int n, int d);// �������� 
};
