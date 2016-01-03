#include "stdafx.h"
#include "BinaryTree.cpp"

int _tmain(int argc, _TCHAR* argv[])
{ 
	BinaryTree<int> tree;
	int num;    
	printf("测试数据:1/2,3/4,5,N,N\n");
	printf("前序遍历:\n");
	tree.PreOrder();
	printf("\n中序遍历:\n");
	tree.InOrder();
	printf("\n后序遍历:\n");
	tree.PostOrder();
	printf("\n层次遍历:\n");
	tree.LevelOrder();
	printf("\n深度为：%d", tree.Depth());
	printf("\n元素数为：%d", tree.Count());

	char front[100], middle[100];
	printf("\n\n请输入前序：");
	cin >> front;
	printf("请输入中序：");
	cin >> middle;
	printf("后序遍历为：\n");
	tree.SowPostOrder(front, middle);
	printf("\n");
	system("pause");
	return 0;
}

