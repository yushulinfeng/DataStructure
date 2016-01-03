#include "stdafx.h"

/*�����-��ջ*/
//typename���Ա�ʾ�κ����ͣ���classֻ�ܱ�ʾ��
template<typename T, typename container>
class stack
{
public:
	//ջ�Ƿ�Ϊ��
	bool empty() const
	{
		return index == 0;
	}

	//��ջ
	void pop()
	{
		if (empty())
		{
			thrownew exception("ջ��û������");
		}
		arr[index - 1] = 0;
		--index;
	}

	//��ջ�����Ĭ������δ������������ݣ�������������·���һ�����������飬
	//��Ĭ�������е����ݿ����������ͷ�Ĭ������,��ָ��ָ��������
	void push(const T& val)
	{
		if (index <= capacity - 1)
		{
			arr[index++] = val;
		}
		else
		{
			capacity <<= 1;//capacity��Ӧ�Ķ�����������һλ
			int*tmp = newint[capacity];
			for (int i = 0; i<index; i++)
			{
				tmp[i] = arr[i];
			}
			tmp[index++] = val;
			delete arr;
			arr = tmp;
		}
	}

	//ջ��Ԫ�ظ���
	int size() const
	{
		return index;
	}

	stack()
	{
		//Ĭ��ջ���ܴ��4��Ԫ�أ���Ȼ���˵�������ã���Ϊ���û����ջ��������ݣ�ȴ�������ĸ�Ԫ�صĿռ䣬��Ȼ�����롣
		//Ϊ�˱���������⣬������push�����Ŀ�ʼ�ж�ջ���Ƿ���Ԫ�أ����û��Ԫ�أ��Ϳ�ʼ����ռ䣬��Ԫ�ص�Ȼ�Ͳ��ã�
		//�����и��������ÿ�����Ԫ�ض�Ҫ�жϣ�������Ԫ�ؽ϶�Ļ����������������Ҫִ���������ж�
		//��ʽ�����������ǣ�ֻ�е��򲻵��ѵ�����²Ŷ�������ͷ���ռ䣬��Ȼ�Ϳ����Ƕ���Ķ�������Ͳ���Ҫ����Ŀռ�
		//����ĳ�������Ǳ���ģ��û�ʽ��������Ӱ��Ч�ʣ���ΪΪ��ʵ�ֻ�ʽ����Ҳ��Ҫ���۵ġ�
		initialize(4);
	}

	//Ԥ��ջ������cap��Ԫ��
	stack(int cap)
	{
		initialize(cap);
	}

	//explicit��ֹ��������ת��
	explicit stack(const container& cont)
	{
		initialize(cont.size());
		vector <int>::const_iterator iter = cont.begin();
		while (iter != cont.end())
		{
			push(*iter++);
		}
	}

	//����
	~stack()
	{
		delete arr;
	}

	//���ջ��Ԫ��
	T& top()
	{
		return arr[index - 1];
	}

	//��C++�У���������const��non-const
	const T& top() const
	{
		return arr[index - 1];
	}

private:
	int capacity;//����
	int index;//����Ԫ�ص�λ��
	T *arr;//����

	//��ʼ��
	//��Ȼ����ʼ���б�ȸ�ֵЧ�ʸߣ���ֵ�������һ��constructor
	void initialize(int cap)
	{
		capacity = cap;
		arr = new T[capacity];
		index = 0;
	}
};