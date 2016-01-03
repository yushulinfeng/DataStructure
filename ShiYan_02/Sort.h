#include "stdafx.h"

template<class T>
class Sort {
private:
	void Swap(T& a, T& b);//交换两个元素 
	int Max(T a[], int n);//返回最大值所在位置 
	int Partition(T a[], int first, int last);//分区(以最后一个数为KEY,返回其所在位置) 
	void Merge(T a[], int first, int middle, int last);//合并两个有序数组 
public:
	void BubbleSort(T a[], int n);//冒泡排序 
	void SelectionSort(T a[], int n);//选择排序 
	void InsertionSort(T a[], int n);//插入排序 
	void QuickSort(T a[], int first, int last);//快速排序 
	void MergeSort(T a[], int first, int last);//合并排序 
	void RadixSort(T a[], int n, int d);// 基数排序 
};
