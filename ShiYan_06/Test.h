#include "stdafx.h"
//���ԡ�ѧϰר��

//��1���õݹ鷽��������������
//��2���õݹ��㷨�Զ��������������������������ͺ��������������������
//��3���Զ��������в�α������������������
//��4�������������Ȳ����

#include <iostream>
using namespace std;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
}
BiTNode, *BiTree;//����������  

typedef struct QNode
{
	BiTNode data;
	struct QNode *next;
} //������еĽڵ�����  
QNode, *QueuePtr;

typedef struct
{
	QueuePtr  front;
	QueuePtr  rear;
}
LinkQueue;//����  

void InitQueue(LinkQueue *Q)//��������  
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void EnQueue(LinkQueue *Q, BiTNode e)//��Ԫ�����  
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));//Ϊ��㿪�ٿռ�  
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

BiTNode DeQueue(LinkQueue *Q)//��Ԫ�س��в�����Ԫ�ص�ֵ��  
{
	BiTNode e; QueuePtr p;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);//�ͷŽڵ�  
	return (e);
}

int QueueEmpty(LinkQueue *Q)//�ж϶����Ƿ�Ϊ��  
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}

BiTree CreateBiTree()//������  
{
	char p; BiTree T;
	cin >> p;
	cout << p;
	if (p == '`')
		T = NULL;
	else
	{
		T = (BiTNode *)malloc(sizeof(BiTNode));//Ϊ��㿪�ٿռ�  
		T->data = p;
		T->lchild = CreateBiTree();
		T->rchild = CreateBiTree();
	}
	return (T);
}

void PreOrder(BiTree T)//ǰ��
{
	if (T != NULL)
	{
		printf("%c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void InOrder(BiTree T)//����  
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		printf("%c", T->data);
		InOrder(T->rchild);
	}
}
void PostOrder(BiTree T)//����  
{
	if (T != NULL)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c", T->data);
	}
}

void LevelOrder(BiTree T)//��α���  
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

int Depth(BiTree T)/* ��� */
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