#include "stdafx.h"
//优先队列：堆MaxHeap的定义与使用
#include <iostream>
using namespace std;

void OutOfBounds(){
	cout << "Out Of Bounds!" << endl;
}


void BadInput(){
	cout << "Bad Input!" << endl;
}


void NoMem(){
	cout << "No Memory!" << endl;
}

template<class T>
class MaxHeap{
public:
	MaxHeap(int MaxHeapSize = 10);
	int Size()const{ return CurrentSize; }
	T Max(){
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}

	MaxHeap<T>& Insert(const T&x);
	MaxHeap<T>& DeleteMax(T&x);
	void Initialize(T a[], int size, int ArraySize);
	void Output(ostream& out)const;

	int CurrentSize;
	int MaxSize;
	T *heap;//元素数组	
};


//输出链表  
template<class T>
void MaxHeap<T>::Output(ostream& out)const{
	for (int i = 0; i<CurrentSize; i++)
	{
		cout << heap[i + 1] << "  ";
	}
	cout << endl;
}
//重载操作符  
template<class T>
ostream& operator<<(ostream& out, const MaxHeap<T>&x){
	x.Output(out);
	return out;
}

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize /* = 10 */){
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}

//将x插入到最大堆中
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T&x){
	if (CurrentSize == MaxSize)
		throw NoMem();

	//为x寻找插入位置
	//i从新的叶结点开始，并沿着树慢慢上升
	int i = ++CurrentSize;
	while (i != 1 && x>heap[i / 2]){
		//不能把x放到heap[i]
		heap[i] = heap[i / 2];//将元素下移
		i /= 2;
	}
	heap[i] = x;
	return *this;
}


//将最大的元素放到x并从堆中删除
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T&x){
	//检查堆是否为空
	if (CurrentSize == 0)
		throw OutOfBounds();

	x = heap[1];					//取出最大元素并放入x中
	T y = heap[CurrentSize];		//y为最后一个元素

	CurrentSize--;

	//从根开始为y寻找合适的位置
	int i = 1;			//堆的当前节点
	int ci = 2;			//i的孩子
	while (ci <= CurrentSize){
		//heap[ci]应该是较大的孩子
		if (ci<CurrentSize&&heap[ci]<heap[ci + 1])
			ci++;

		//能否把y放入heap[i]
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci = 2 * ci;
	}

	heap[i] = y;
	return *this;
}


//把最大堆初始化为数组a
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize){
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;//数组空间大小

	//产生一个最大堆
	for (int i = CurrentSize / 2; i >= 1; i--){

		T y = heap[i];		//子树的根

		//寻找放置y的位置
		int c = 2 * i;	//c的父节点是y的目标位置

		while (c <= CurrentSize){

			//heap[c]应该是较大的同胞节点
			if (c<CurrentSize&&heap[c]<heap[c + 1])
				c++;

			//能否把y放入heap[c/2]
			if (y >= heap[c])		//能把y放入heap[c/2]
				break;

			//不能把y放入heap[c/2]
			heap[c / 2] = heap[c];	//将孩子上移
			c = 2 * c;				//下移一层

		}
		heap[c / 2] = y;
	}
}

template<class T>
void HeapSort(T a[], int n)
{
	MaxHeap<T>H;
	H.Initialize(a, n, 20);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		a[i + 1] = x;
	}
}

//int main(){
//	MaxHeap<int>myHeap;
//	const int number = 10;
//	int myArray[number + 1] = { -1, 6, 8, 4, 2, 1, 3, 0, 5, 7, 9 };
//	myHeap.Initialize(myArray, number, 20);
//	cout << myHeap << endl;
//
//	HeapSort(myArray, number);
//	for (int j = 1; j <= number; j++)
//	{
//		cout << myArray[j] << "  ";
//	}
//	cout << endl;
//
//	return 0;
//}