#include "stdafx.h"

/*1��	���������ࡣ���ѵĴ洢�ṹʹ������
2��	�ṩ����:�ѵĲ��롢�ѵ�ɾ�����ѵĳ�ʼ����Huffman���Ĺ��졣�����������Ĺ��졣
3��	���ռ���¼���һϵ��������������Ӧ�����ѡ�Huffman�����Լ�������������
4��	������
*/
//���ȶ��У���MaxHeap�Ķ�����ʹ��
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
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
	for (int i = 0; i < CurrentSize; i++)
	{
		cout << heap[i + 1] << " ";
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
	while (i != 1 && x > heap[i / 2]){
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
		OutOfBounds();

	x = heap[1];					//ȡ�����Ԫ�ز�����x��
	T y = heap[CurrentSize];		//yΪ���һ��Ԫ��

	CurrentSize--;

	//�Ӹ���ʼΪyѰ�Һ��ʵ�λ��
	int i = 1;			//�ѵĵ�ǰ�ڵ�
	int ci = 2;			//i�ĺ���
	while (ci <= CurrentSize){
		//heap[ci]Ӧ���ǽϴ�ĺ���
		if (ci < CurrentSize&&heap[ci] < heap[ci + 1])
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
			if (c < CurrentSize&&heap[c] < heap[c + 1])
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

//����������   ����������
struct node
{
	int key;
	struct node *l;
	struct node *r;
};

//typedef struct node *pnode;
int mark[100];
struct node  huffman[100];
struct node  bstree[100];
void PrintNode(struct node *node)
{
	cout << node->key << " ";
}

void PreOrder(struct node *T)
{
	if (T)
	{
		PrintNode(T);
		PreOrder(T->l);
		PreOrder(T->r);
	}
}

////////
void MidOrder(struct node *T)
{
	if (T)
	{
		MidOrder(T->l);
		PrintNode(T);
		MidOrder(T->r);
	}
}

////ѡ����С�ġ��ڶ�С�������ڵ�
void Choose(int *mark, struct node *huffman, int size, int *choose)
{
	int i;
	int minkey = 0;
	int tkey = 0;
	int temp = 0;
	//�ҵ���һ��δ��ǵ�λ��
	for (i = 0; i < size; i++){
		if (!mark[i]){
			minkey = i;
			i++;
			break;
		}
	}
	tkey = minkey;
	for (; i < size; i++){
		if (!mark[i]){
			//�ڶ���δ��ǵ�λ�ã�ֻ���״ε��˲���true��
			if (tkey == minkey) 
				tkey = i;
			//����Сֵ����Сֵ
			if (huffman[i].key < huffman[minkey].key){
				tkey = minkey;
				minkey = i;
			}
			//���������first mark=min��
			if (huffman[i].key < huffman[tkey].key  && i != minkey){
				tkey = i;
			}
		}
	}
	choose[0] = minkey;
	choose[1] = tkey;
}

struct node HuffmanTree(int *mark, struct node *huffman, int size)
{
	int choose[2];
	int i;
	struct node *mynode;
	for (i = 0; i < size - 1; i++)
	{
		////ѡ����С�ġ��ڶ�С�������ڵ�
		Choose(mark, huffman, size, choose);
		////�ϲ��������ڵ�
		mynode = new node();
		mynode->key = huffman[choose[0]].key + huffman[choose[1]].key;//����keyֵ
		mynode->l = new node();
		mynode->l->key = huffman[choose[0]].key;
		mynode->l->l = huffman[choose[0]].l;
		mynode->l->r = huffman[choose[0]].r;
		mynode->r = &huffman[choose[1]];
		////ˢ�½ڵ����飨���µĽڵ��滻��С�Ľڵ㣬���ڶ�С�Ľڵ������ʹ�õı�ǣ�
		////��ʵ���൱�ڼ����µĽڵ㣬ɾȥ�ɵĽڵ�
		huffman[choose[0]] = *mynode;
		mark[choose[1]] = 1;
		free(mynode);
	}
	return huffman[choose[0]];
}

struct node *bstreeinsert(struct node *bstree)
{
	node *rt = 0;
	for (int i = 0; i < 10; i++)
	{
		int e = bstree[i].key;
		node *p = rt, *parent = 0;//����ָ��͸��ڵ�ָ��
		while (p){
			parent = p;
			if (e < p->key) p = p->l;
			else if (e>p->key) p = p->r;
			else{
				cout << "error" << endl;
				break;
			}
		}
		//Ϊe����һ���ڵ㣬�����ýڵ�������parent
		node *t = new node();
		t->key = e;
		if (rt)
			if (e < parent->key) parent->l = t;
			else parent->r = t;
		else //�׸��ڵ�
			rt = t;
	}
	return rt;
}

int _tmain(int argc, _TCHAR* argv[]){
	MaxHeap<int> myHeap;
	const int number = 10;
	int s;
	int key[10] = { 1, 4, 7, 8, 5, 2, 3, 6, 9, 0 };
	////��Ҫʹ�ü������룬����Щע��ȡ������
	//cout << "������10������" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cin >> s;
	//	key[i] = s;
	//}
	cout << "ԭ���飺" << endl;
	for (int i = 0; i < 10; i++)
		cout << key[i] << " ";
	cout << endl << endl;

	int myArray[11];////////
	for (int i = 0; i < 10; i++)
	{
		myArray[i + 1] = key[i];
	}
	myArray[0] = -1;
	myHeap.Initialize(myArray, number, 20);
	cout << "���ѣ�����:" << endl;
	cout << myHeap;
	HeapSort(myArray, number);
	cout << "������:" << endl;
	for (int j = 1; j <= number; j++)
	{
		cout << myArray[j] << " ";
	}
	cout << endl << endl;

	cout << "Huffman����:" << endl;
	int i;
	struct node huffmantree;
	memset(mark, 0, sizeof(mark));
	memset(huffman, 0, sizeof(huffman));
	for (i = 0; i < 10; i++)
	{
		huffman[i].key = key[i];
	}
	huffmantree = HuffmanTree(mark, huffman, 10);
	cout << "ǰ��";
	PreOrder(&huffmantree);
	cout << "\n����";
	MidOrder(&huffmantree);
	cout << endl << endl;

	cout << "������������" << endl;
	struct node *bs;
	for (int i = 0; i < 10; i++)
	{
		bstree[i].key = key[i];
	}
	bs = bstreeinsert(bstree);
	cout << "ǰ��";
	PreOrder(bs);
	cout << "\n����";
	MidOrder(bs);////////����������������������������������ģ�
	cout << endl;
	system("pause");
	return 0;
}


