#include "stdafx.h"
using namespace std;

/*链表版-堆栈*/

//链表结点
template<class T>
class node
{
public:
	T val;
	node *next;
	node() :next(NULL){}
	node(T v) :val(v), next(NULL){}
};

//堆栈
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
	//出栈
	void pop(){
		if (empty()){//空栈
			throw new exception("栈中没有数据");
			return;
		}
		if (head->next == cur){//删除第一个元素
			delete cur;
			head->next = NULL;
		}else{ //删除最后一个元素
			node *tmp = head->next;
			//将指针移到最后第二个元素
			for (int i = 2; i<len; i++)
				tmp = tmp->next;
			delete tmp->next; //析构最后一个元素
			cur = tmp;//将指针指到现在的最后一个元素
		}
		--len;//元素个数减一
	}

	//入栈
	void push(const T& val)
	{
		node *tmp = new node(val);//新建节点
		cur->next = tmp;//将当前节点的下一个节点指向新增节点
		cur = tmp;//当前节点指向新节点
		++len;//节点个数加1
	}
private:
	int len;//元素个数
	node *head;//表头节点
	node *cur;//当前节点
};

