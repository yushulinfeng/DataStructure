#include "stdafx.h"
#include "maxHeap.cpp" 
#include "Huffman.h"
#include "binarySearchTree.h"

//堆排序
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
	//先构造一棵普通的完全二叉树
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
	cout << "普通二叉树（层次遍历）:" << endl;
	tree1.leverOrderTraverse(t1);
	cout << endl;

	maxHeap<int> heap;
	heap.Initialize(tree1);
	cout << "初始化为最大堆（层次遍历）:" << endl;
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
	cout << "树中是否存在8：" << b << endl;
	cout << "树中最小元素：" << x << endl;
	x = binaryTree.findMax();
	cout << "树中最大元素：" << x << endl;
	cout << x << endl;
	cout << "前序遍历：" << endl;
	binaryTree.printTreeInPrev();
	cout << endl;
	cout << "中序遍历：" << endl;
	binaryTree.printTreeInMid();
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{ 
	testMaxHeap();
	int n;
	cout << "\n请输入数组长度：";
	cin >> n;
	int *input;
	input = new int[n];
	cout << "请依次输入数值：";
	for (int i = 0; i < n; i++){
		cin >> input[i];
	}
	cout << "原数组:" << endl;
	for (int i = 0; i < n; i++)
		cout << input[i] << " ";
	cout << endl << endl;

	BinarySearchTree<int> binaryTree;
	for (int i = 0; i < n; i++){
		binaryTree.insert(input[i]);
	}
	cout << "--二叉搜索树--" << endl;
	cout << "前序遍历：" << endl;
	binaryTree.printTreeInPrev();
	cout << endl;
	cout << "中序遍历：" << endl;
	binaryTree.printTreeInMid(); 
	cout << endl << endl;

	cout << "--Huffman编码--" << endl;
	HuffmanCode huff(input, n); 
	cout << "前序：";
	huff.PreOrder();      
	cout << "\n中序：";
	huff.MidOrder();
	cout << "\n编码输出：\n";
	huff.PrintCode();      

	cout << "--最大堆--" << endl;
	maxHeap<int> temp_heap;
	for (int i = 0; i < n; i++){
		temp_heap.Insert(input[i]);
	}
	cout << "最大堆（层次遍历）:" << endl;
	temp_heap.Output();
	cout << endl;
	cout << "堆排序:" << endl;
	HeapSort(input, n);//堆排序
	int temp_int = 0;
	for (int i = 0; i < n; i++){
		cout << input[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

