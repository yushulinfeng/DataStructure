#include "stdafx.h"
#include "BinaryTree.cpp"

int _tmain(int argc, _TCHAR* argv[])
{ 
	BinaryTree<int> tree;
	int num;    
	printf("��������:1/2,3/4,5,N,N\n");
	printf("ǰ�����:\n");
	tree.PreOrder();
	printf("\n�������:\n");
	tree.InOrder();
	printf("\n�������:\n");
	tree.PostOrder();
	printf("\n��α���:\n");
	tree.LevelOrder();
	printf("\n���Ϊ��%d", tree.Depth());
	printf("\nԪ����Ϊ��%d", tree.Count());

	char front[100], middle[100];
	printf("\n\n������ǰ��");
	cin >> front;
	printf("����������");
	cin >> middle;
	printf("�������Ϊ��\n");
	tree.SowPostOrder(front, middle);
	printf("\n");
	system("pause");
	return 0;
}

