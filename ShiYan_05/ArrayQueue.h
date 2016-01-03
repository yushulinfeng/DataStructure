#include "stdafx.h"
/*数组版-队列*/
template<typename T, typename container>
class queue
{
public:
	bool empty() const
	{
		return head == rail;
	}

	void checkEmpty()
	{
		if (empty())
		{
			throw new exception("队列中没有数据");
		}
	}

	//队尾元素
	T& back()
	{
		checkEmpty();
		return arr[rail - 1];
	}

	const T& back() const
	{
		return back();
	}

	//出队
	void pop()
	{
		checkEmpty();
		arr[head++] = 0;
	}

	//队头元素
	T& front()
	{
		checkEmpty();
		return arr[head];
	}

	const T& front() const
	{
		return front();
	}

	//入队
	void push(const T& val)
	{
		if (rail >= capacity){
			capacity = (rail - head) * 2;
			T *tmp = new T[capacity];
			int j = 0;
			for (int i = head; i<rail; i++)
			{
				tmp[j++] = arr[i];
			}
			delete arr;
			arr = tmp;
			rail = rail - head;
			head = 0;
		}
		arr[rail++] = val;
	}

	queue()
	{
		initialize(4);
	}

	queue(int capacity)
	{
		initialize(capacity);
	}

	explicit queue(const container& cont)
	{
		initialize(cont.size());
		vector <int>::const_iterator iter = cont.begin();
		while (iter != cont.end())
		{
			push(*iter++);
		}
	}

	~queue()
	{
		delete arr;
	}

	//队列中元素个数
	int size()
	{
		return rail - head;
	}

protected:
	typedef struct node1
	{
		node1 *next;
		T val;
		node1(T v) :val(v), next(NULL){}
	}node;

private:
	int capacity;
	int head;//对头元素的位置
	int rail;//对尾元素的位置
	int *arr;

	void initialize(int cap)
	{
		capacity = cap;
		arr = new int[capacity];
		head = rail = 0;
	}
};