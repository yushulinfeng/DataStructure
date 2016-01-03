#include "stdafx.h"
//���ȶ��У���MaxHeap�Ķ�����ʹ��
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
	T *heap;//Ԫ������	
};


//�������  
template<class T>
void MaxHeap<T>::Output(ostream& out)const{
	for (int i = 0; i<CurrentSize; i++)
	{
		cout << heap[i + 1] << "  ";
	}
	cout << endl;
}
//���ز�����  
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

//��x���뵽������
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T&x){
	if (CurrentSize == MaxSize)
		throw NoMem();

	//ΪxѰ�Ҳ���λ��
	//i���µ�Ҷ��㿪ʼ������������������
	int i = ++CurrentSize;
	while (i != 1 && x>heap[i / 2]){
		//���ܰ�x�ŵ�heap[i]
		heap[i] = heap[i / 2];//��Ԫ������
		i /= 2;
	}
	heap[i] = x;
	return *this;
}


//������Ԫ�طŵ�x���Ӷ���ɾ��
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T&x){
	//�����Ƿ�Ϊ��
	if (CurrentSize == 0)
		throw OutOfBounds();

	x = heap[1];					//ȡ�����Ԫ�ز�����x��
	T y = heap[CurrentSize];		//yΪ���һ��Ԫ��

	CurrentSize--;

	//�Ӹ���ʼΪyѰ�Һ��ʵ�λ��
	int i = 1;			//�ѵĵ�ǰ�ڵ�
	int ci = 2;			//i�ĺ���
	while (ci <= CurrentSize){
		//heap[ci]Ӧ���ǽϴ�ĺ���
		if (ci<CurrentSize&&heap[ci]<heap[ci + 1])
			ci++;

		//�ܷ��y����heap[i]
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci = 2 * ci;
	}

	heap[i] = y;
	return *this;
}


//�����ѳ�ʼ��Ϊ����a
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize){
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;//����ռ��С

	//����һ������
	for (int i = CurrentSize / 2; i >= 1; i--){

		T y = heap[i];		//�����ĸ�

		//Ѱ�ҷ���y��λ��
		int c = 2 * i;	//c�ĸ��ڵ���y��Ŀ��λ��

		while (c <= CurrentSize){

			//heap[c]Ӧ���ǽϴ��ͬ���ڵ�
			if (c<CurrentSize&&heap[c]<heap[c + 1])
				c++;

			//�ܷ��y����heap[c/2]
			if (y >= heap[c])		//�ܰ�y����heap[c/2]
				break;

			//���ܰ�y����heap[c/2]
			heap[c / 2] = heap[c];	//����������
			c = 2 * c;				//����һ��

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