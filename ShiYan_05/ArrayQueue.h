#include "stdafx.h"
/*�����-����*/
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
			throw new exception("������û������");
		}
	}

	//��βԪ��
	T& back()
	{
		checkEmpty();
		return arr[rail - 1];
	}

	const T& back() const
	{
		return back();
	}

	//����
	void pop()
	{
		checkEmpty();
		arr[head++] = 0;
	}

	//��ͷԪ��
	T& front()
	{
		checkEmpty();
		return arr[head];
	}

	const T& front() const
	{
		return front();
	}

	//���
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

	//������Ԫ�ظ���
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
	int head;//��ͷԪ�ص�λ��
	int rail;//��βԪ�ص�λ��
	int *arr;

	void initialize(int cap)
	{
		capacity = cap;
		arr = new int[capacity];
		head = rail = 0;
	}
};