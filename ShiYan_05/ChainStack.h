#include "stdafx.h"
using namespace std;

/*�����-��ջ*/

//������
template<class T>
class node
{
public:
	T val;
	node *next;
	node() :next(NULL){}
	node(T v) :val(v), next(NULL){}
};

//��ջ
template<class T>
class stack
{
public:
	stack(){
		head = new node<T>();
		cur = head;
		len = 0;
	}
	~stack(){ delete head; }
	int size() const{ return len; }
	bool empty() const{return len == 0;}
	T& top()
	{
		if (empty()) return NULL;
		return cur->val;
	}
	//��ջ
	void pop(){
		if (empty()){//��ջ
			throw new exception("ջ��û������");
			return;
		}
		if (head->next == cur){//ɾ����һ��Ԫ��
			delete cur;
			head->next = NULL;
		}else{ //ɾ�����һ��Ԫ��
			node *tmp = head->next;
			//��ָ���Ƶ����ڶ���Ԫ��
			for (int i = 2; i<len; i++)
				tmp = tmp->next;
			delete tmp->next; //�������һ��Ԫ��
			cur = tmp;//��ָ��ָ�����ڵ����һ��Ԫ��
		}
		--len;//Ԫ�ظ�����һ
	}

	//��ջ
	void push(const T& val)
	{
		node *tmp = new node(val);//�½��ڵ�
		cur->next = tmp;//����ǰ�ڵ����һ���ڵ�ָ�������ڵ�
		cur = tmp;//��ǰ�ڵ�ָ���½ڵ�
		++len;//�ڵ������1
	}
private:
	int len;//Ԫ�ظ���
	node *head;//��ͷ�ڵ�
	node *cur;//��ǰ�ڵ�
};

