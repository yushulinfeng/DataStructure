#include "stdafx.h"

/*1、	创建最大堆类。最大堆的存储结构使用链表。
2、	提供操作:堆的插入、堆的删除。堆的初始化。Huffman树的构造。二叉搜索树的构造。
3、	接收键盘录入的一系列整数，输出其对应的最大堆、Huffman编码以及二叉搜索树。
4、	堆排序。
*/
//优先队列：堆MaxHeap的定义与使用
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
	T *heap;//元素数组
};


//输出链表
template<class T>
void MaxHeap<T>::Output(ostream& out)const{
	for (int i = 0; i < CurrentSize; i++)
	{
		cout << heap[i + 1] << " ";
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
	while (i != 1 && x > heap[i / 2]){
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
		OutOfBounds();

	x = heap[1];					//取出最大元素并放入x中
	T y = heap[CurrentSize];		//y为最后一个元素

	CurrentSize--;

	//从根开始为y寻找合适的位置
	int i = 1;			//堆的当前节点
	int ci = 2;			//i的孩子
	while (ci <= CurrentSize){
		//heap[ci]应该是较大的孩子
		if (ci < CurrentSize&&heap[ci] < heap[ci + 1])
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
			if (c < CurrentSize&&heap[c] < heap[c + 1])
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

//哈夫曼编码   二叉搜索树
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

////选出最小的、第二小的两个节点
void Choose(int *mark, struct node *huffman, int size, int *choose)
{
	int i;
	int minkey = 0;
	int tkey = 0;
	int temp = 0;
	//找到第一个未标记的位置
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
			//第二个未标记的位置（只有首次到此才是true）
			if (tkey == minkey) 
				tkey = i;
			//找最小值、次小值
			if (huffman[i].key < huffman[minkey].key){
				tkey = minkey;
				minkey = i;
			}
			//特殊情况（first mark=min）
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
		////选出最小的、第二小的两个节点
		Choose(mark, huffman, size, choose);
		////合并这两个节点
		mynode = new node();
		mynode->key = huffman[choose[0]].key + huffman[choose[1]].key;//更新key值
		mynode->l = new node();
		mynode->l->key = huffman[choose[0]].key;
		mynode->l->l = huffman[choose[0]].l;
		mynode->l->r = huffman[choose[0]].r;
		mynode->r = &huffman[choose[1]];
		////刷新节点数组（用新的节点替换最小的节点，将第二小的节点添加已使用的标记）
		////其实就相当于加了新的节点，删去旧的节点
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
		node *p = rt, *parent = 0;//搜索指针和父节点指针
		while (p){
			parent = p;
			if (e < p->key) p = p->l;
			else if (e>p->key) p = p->r;
			else{
				cout << "error" << endl;
				break;
			}
		}
		//为e建立一个节点，并将该节点连接至parent
		node *t = new node();
		t->key = e;
		if (rt)
			if (e < parent->key) parent->l = t;
			else parent->r = t;
		else //首个节点
			rt = t;
	}
	return rt;
}

int _tmain(int argc, _TCHAR* argv[]){
	MaxHeap<int> myHeap;
	const int number = 10;
	int s;
	int key[10] = { 1, 4, 7, 8, 5, 2, 3, 6, 9, 0 };
	////若要使用键盘输入，把这些注释取消即可
	//cout << "请输入10个数：" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cin >> s;
	//	key[i] = s;
	//}
	cout << "原数组：" << endl;
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
	cout << "最大堆（层序）:" << endl;
	cout << myHeap;
	HeapSort(myArray, number);
	cout << "堆排序:" << endl;
	for (int j = 1; j <= number; j++)
	{
		cout << myArray[j] << " ";
	}
	cout << endl << endl;

	cout << "Huffman编码:" << endl;
	int i;
	struct node huffmantree;
	memset(mark, 0, sizeof(mark));
	memset(huffman, 0, sizeof(huffman));
	for (i = 0; i < 10; i++)
	{
		huffman[i].key = key[i];
	}
	huffmantree = HuffmanTree(mark, huffman, 10);
	cout << "前序：";
	PreOrder(&huffmantree);
	cout << "\n中序：";
	MidOrder(&huffmantree);
	cout << endl << endl;

	cout << "二叉搜索树：" << endl;
	struct node *bs;
	for (int i = 0; i < 10; i++)
	{
		bstree[i].key = key[i];
	}
	bs = bstreeinsert(bstree);
	cout << "前序：";
	PreOrder(bs);
	cout << "\n中序：";
	MidOrder(bs);////////中序遍历（二叉搜索树的中序遍历是有序的）
	cout << endl;
	system("pause");
	return 0;
}


