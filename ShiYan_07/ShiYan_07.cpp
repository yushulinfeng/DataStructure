#include "stdafx.h"
#include "maxHeap.cpp" 
#include "Huffman.h"
#include "binarySearchTree.h"

//������
template <class T>
void HeapSort(T* arrays, int array_length){
	maxHeap<T> temp_heap;
	for (int i = 0; i < array_length; i++){
		temp_heap.Insert(arrays[i]);
	}
	int temp_int = 0;
	for (int i = 0; i < array_length; i++){
		temp_heap.DeleteMax(temp_int);
		arrays[i] = temp_int;
	}
}

void testMaxHeap()
{
	//�ȹ���һ����ͨ����ȫ������
	binaryTreeNode<int> *t1, *t3, *t4, *t5, *t6;
	binaryTree<int> tree1(20);
	int element[] = { 4, 3, 5, 10, 8, 6, 7, 2, 1 };
	t1 = tree1.getRoot();
	tree1.insertLeftChild(t1, element[0]);
	tree1.insertRightChild(t1, element[1]);
	t3 = t1->getLeftChild();
	tree1.insertLeftChild(t3, element[2]);
	tree1.insertRightChild(t3, element[3]);
	t4 = t1->getRightChild();
	tree1.insertLeftChild(t4, element[4]);
	tree1.insertRightChild(t4, element[5]);
	t5 = t3->getLeftChild();
	tree1.insertLeftChild(t5, element[6]);
	tree1.insertRightChild(t5, element[7]);
	t6 = t3->getRightChild();
	tree1.insertLeftChild(t6, element[8]);
	cout << "��ͨ����������α�����:" << endl;
	tree1.leverOrderTraverse(t1);
	cout << endl;

	maxHeap<int> heap;
	heap.Initialize(tree1);
	cout << "��ʼ��Ϊ���ѣ���α�����:" << endl;
	heap.Output();
	cout << endl;
}
 
void testSearchTree()
{ 
	BinarySearchTree<int> binaryTree;
	int ele[] = { 5, 1, 2, 3, 6, 8 };
	for (int i = 0; i < 6; i++){
		binaryTree.insert(ele[i]);
	}
	bool b = binaryTree.contains(8);
	int x = binaryTree.findMin();
	cout << "�����Ƿ����8��" << b << endl;
	cout << "������СԪ�أ�" << x << endl;
	x = binaryTree.findMax();
	cout << "�������Ԫ�أ�" << x << endl;
	cout << x << endl;
	cout << "ǰ�������" << endl;
	binaryTree.printTreeInPrev();
	cout << endl;
	cout << "���������" << endl;
	binaryTree.printTreeInMid();
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{ 
	testMaxHeap();
	int n;
	cout << "\n���������鳤�ȣ�";
	cin >> n;
	int *input;
	input = new int[n];
	cout << "������������ֵ��";
	for (int i = 0; i < n; i++){
		cin >> input[i];
	}
	cout << "ԭ����:" << endl;
	for (int i = 0; i < n; i++)
		cout << input[i] << " ";
	cout << endl << endl;

	BinarySearchTree<int> binaryTree;
	for (int i = 0; i < n; i++){
		binaryTree.insert(input[i]);
	}
	cout << "--����������--" << endl;
	cout << "ǰ�������" << endl;
	binaryTree.printTreeInPrev();
	cout << endl;
	cout << "���������" << endl;
	binaryTree.printTreeInMid(); 
	cout << endl << endl;

	cout << "--Huffman����--" << endl;
	HuffmanCode huff(input, n); 
	cout << "ǰ��";
	huff.PreOrder();      
	cout << "\n����";
	huff.MidOrder();
	cout << "\n���������\n";
	huff.PrintCode();      

	cout << "--����--" << endl;
	maxHeap<int> temp_heap;
	for (int i = 0; i < n; i++){
		temp_heap.Insert(input[i]);
	}
	cout << "���ѣ���α�����:" << endl;
	temp_heap.Output();
	cout << endl;
	cout << "������:" << endl;
	HeapSort(input, n);//������
	int temp_int = 0;
	for (int i = 0; i < n; i++){
		cout << input[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

