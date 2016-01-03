#include "stdafx.h"

struct Node
{
	char data;
	int weight;
	Node *next;
};
class Linklist
{
public:
	Linklist(){ rear = new Node; rear = rear->next; }
	void Construct(char s[]);
	int Getlength();
	Node*rear;

};
void Linklist::Construct(char s[])
{
	rear = new Node;
	rear->next = rear;
	for (unsigned int i = 0; i<strlen(s); i++)
	{
		if (rear->next == rear)
		{
			Node *p = new Node;
			p->data = s[0];
			p->weight = 1;
			p->next = rear->next;
			rear->next = p;
			rear = p;
		}
		else
		{
			Node *q = rear->next->next;
			while (q != rear->next)
			{
				if (q->data == s[i])
				{
					q->weight++;
					break;
				}
				else
					q = q->next;
			}
			if (q == rear->next)
			{
				Node *r = new Node;
				r->data = s[i];
				r->weight = 1;
				r->next = rear->next;
				rear->next = r;
				rear = r;
			}
		}
	}
}

int Linklist::Getlength()
{
	int n = 0;
	Node*t = rear->next->next;
	while (t != rear->next)
	{
		t = t->next;
		n++;
	}
	return n;
}