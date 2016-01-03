#include "stdafx.h"
//测试、学习专用

//（1）用递归方法创建二叉链表
//（2）用递归算法对二叉树进行先序遍历，中序遍历和后序遍历，并输出遍历结果
//（3）对二叉树进行层次遍历，并输出遍历序列
//（4）求二叉树的深度并输出

#include <iostream>
using namespace std;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
}
BiTNode, *BiTree;//定义结点类型  

typedef struct QNode
{
	BiTNode data;
	struct QNode *next;
} //定义队列的节点类型  
QNode, *QueuePtr;

typedef struct
{
	QueuePtr  front;
	QueuePtr  rear;
}
LinkQueue;//队列  

void InitQueue(LinkQueue *Q)//创建队列  
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void EnQueue(LinkQueue *Q, BiTNode e)//将元素入队  
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));//为结点开辟空间  
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

BiTNode DeQueue(LinkQueue *Q)//将元素出列并返回元素的值。  
{
	BiTNode e; QueuePtr p;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);//释放节点  
	return (e);
}

int QueueEmpty(LinkQueue *Q)//判断队列是否为空  
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}

BiTree CreateBiTree()//创建树  
{
	char p; BiTree T;
	cin >> p;
	cout << p;
	if (p == '`')
		T = NULL;
	else
	{
		T = (BiTNode *)malloc(sizeof(BiTNode));//为结点开辟空间  
		T->data = p;
		T->lchild = CreateBiTree();
		T->rchild = CreateBiTree();
	}
	return (T);
}

void PreOrder(BiTree T)//前序
{
	if (T != NULL)
	{
		printf("%c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void InOrder(BiTree T)//中序  
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		printf("%c", T->data);
		InOrder(T->rchild);
	}
}
void PostOrder(BiTree T)//后序  
{
	if (T != NULL)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c", T->data);
	}
}

void LevelOrder(BiTree T)//层次遍历  
{
	LinkQueue Q; BiTNode p;
	InitQueue(&Q);
	EnQueue(&Q, *T);
	while (!QueueEmpty(&Q))
	{
		p = DeQueue(&Q);
		printf("%c", p.data);
		if (p.lchild != NULL)
			EnQueue(&Q, *(p.lchild));
		if (p.rchild != NULL)
			EnQueue(&Q, *(p.rchild));
	}
}

int Depth(BiTree T)/* 深度 */
{
	int num1, num2;
	if (T == NULL)
		return(0);
	num1 = Depth(T->lchild);
	num2 = Depth(T->rchild);
	if (num1>num2)
		return(num1 + 1);
	else
		return(num2 + 1);
}