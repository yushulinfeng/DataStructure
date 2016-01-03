#include "stdafx.h"

/*链表版-队列*/
template<typename T, typename container>
class queue
{
public:
	bool empty() const{
		return len == 0;
	}

	void checkEmpty(){
		if (empty())
			throw new exception("队列中没有数据");
	}

	T& back(){
		checkEmpty();
		return cur->val;
	}

	const T& back() const{
		return back();
	}

	void pop(){
		checkEmpty();
		if (head->next == cur){
			delete head->next;
			head->next = NULL;
		}else{
			node* tmp = head->next;
			head->next = tmp->next;
			delete tmp;
		}
		--len;
	}

	T& front(){
		checkEmpty();
		return head->next->val;
	}

	const T& front() const{
		return front();
	}

	void push(const T& val){
		node *tmp = new node(val);
		cur->next = tmp;
		cur = tmp;
		++len;
	}

	queue(){
		initialize();
	}

	explicit queue(const container& cont){
		initialize();
		vector <int>::const_iterator iter = cont.begin();
		while (iter != cont.end())
		{
			push(*iter++);
		}
	}

	~queue(){
		node *tmp;
		while (tmp != NULL)
		{
			tmp = head;
			head = head->next;
			delete tmp;
			tmp = NULL;
		}
		delete cur;
	}


	int size(){
		return len;
	}

protected:
	typedef struct node1
	{
		node1 *next;
		T val;
		node1(T v) :val(v), next(NULL){}
	}node;

private:
	int len;
	node *head;
	node *cur;
	void initialize()
	{
		head = new node(-1);
		cur = head;
		len = 0;
	}
};