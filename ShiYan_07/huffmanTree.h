#include "stdafx.h"
#include "Linklist.h"

struct HCode
{
	char data;
	char code[100];
};
struct HNode
{
	int weight;  //节点权值
	int parent;  //双亲指针
	int lchild;  //左孩子指针
	int rchild;  //右孩子指针
};
class Huffman
{
public:
	HNode*HTree;  //哈夫曼树
	HCode*HCodeTable; //哈弗曼编码表
	void CreateHTree(int a[], int n);//创建哈夫曼树
	void CreateTable(char b[], int n);//创建编码表
	void Encoding(char*s, int n);//编码
	void Decoding(char*s, char*d, int n);//解码
	void DestroyTree(int n);//析构
};

void Huffman::DestroyTree(int n)
{
	for (int i = 0; i<2 * n - 3; i++)//析构哈夫曼树
	{
		HNode*p = HTree;
		HTree++;
		delete p;
	}
	for (int j = 0; j<n - 5; j++)//析构编码表
	{
		HCode*q = HCodeTable;
		HCodeTable++;
		delete q;
	}
}

void Huffman::CreateTable(char b[], int n)
{
	HCodeTable = new HCode[n];
	for (int i = 0; i<n; i++)
	{
		HCodeTable[i].data = b[i];//生成编码表
		int child = i;
		int parent = HTree[i].parent;
		int k = 0;
		while (parent != -1)
		{
			if (child == HTree[parent].lchild)
				HCodeTable[i].code[k] = '0';//左孩子标‘0’；
			else
				HCodeTable[i].code[k] = '1';//右孩子标‘1’；
			k++;
			child = parent;
			parent = HTree[child].parent;
		}
		HCodeTable[i].code[k] = '\0';
		char*b = new char[k];
		for (int j = 0; j<k; j++)
		{
			b[j] = HCodeTable[i].code[k - 1 - j];
		}
		for (int jj = 0; jj<k; jj++)
		{
			HCodeTable[i].code[jj] = b[jj];
		}
	}
}

void Huffman::Encoding(char*s, int n)
{
	while (*s != '\0')
	{
		for (int i = 0; i<n; i++)
		{
			if (*s == HCodeTable[i].data)
			{
				cout << HCodeTable[i].code;
				s++;
			}
		}
	}
	cout << endl;
}

void Huffman::Decoding(char*s, char*d, int n)//s为编码串，
{
	while (*s != '\0')
	{
		int parent = 2 * n - 1 - 1;//根节点在HTree中的下标；
		while (HTree[parent].lchild != -1)
		{
			if (*s == '0')
				parent = HTree[parent].lchild;
			else
				parent = HTree[parent].rchild;
			s++;
		}
		*d = HCodeTable[parent].data;
		cout << *d;
		d++;

	}
	cout << endl;
}

void Huffman::CreateHTree(int a[], int n)
{
	HTree = new HNode[2 * n - 1];
	for (int i = 0; i<n; i++)
	{
		HTree[i].weight = a[i];
		HTree[i].lchild = -1;
		HTree[i].rchild = -1;
		HTree[i].parent = -1;
	}
	//选择权值最小的两个结点
	static int k = 0;
	int b2[1000];
	static int x;
	static int y;
	int min = 1000;
	for (int j2 = 0; j2<n; j2++)
	{
		if (HTree[j2].weight<min)
		{
			min = HTree[j2].weight;
			x = j2;
		}
	}
	b2[k] = x;
	k++;
	int _min = 1000;
	for (int j3 = 0; j3<n; j3++)
	{
		int k2;
		for (k2 = 0; k2<k; k2++)
		{
			if (j3 == b2[k2])
				k2 = k + 2;
		}
		if (k2 == k)
		{
			if (HTree[j3].weight >= HTree[x].weight)
			{
				if (HTree[j3].weight<_min)
				{
					_min = HTree[j3].weight;
					y = j3;
				}
			}
		}
	}
	b2[k] = y;
	k++;
	HTree[x].parent = HTree[y].parent = n;
	HTree[n].weight = HTree[x].weight + HTree[y].weight;
	HTree[n].lchild = x;
	HTree[n].rchild = y;
	HTree[n].parent = -1;
	for (int i2 = n + 1; i2<2 * n - 1; i2++) 
	{
		min = 1000;
		for (int j2 = 0; j2<i2; j2++)
		{
			int k2;
			for (k2 = 0; k2<k; k2++)
			{
				if (j2 == b2[k2])
					k2 = k + 2;
			}
			if (k2 == k)
			{
				if (HTree[j2].weight >= HTree[y].weight)
				{
					if (HTree[j2].weight<min)
					{
						min = HTree[j2].weight;
						x = j2;
					}
				}
			}
		}
		b2[k] = x;
		k++;
		int _min = 1000;
		for (int j3 = 0; j3<i2; j3++)
		{
			int k2;
			for (k2 = 0; k2<k; k2++)
			{
				if (j3 == b2[k2])
					k2 = k + 2;
			}
			if (k2 == k)
			{
				if (HTree[j3].weight >= HTree[x].weight)
				{
					if (HTree[j3].weight<_min)
					{
						_min = HTree[j3].weight;
						y = j3;
					}
				}
			}
		}
		b2[k] = y;
		k++;
		HTree[x].parent = HTree[y].parent = i2;
		HTree[i2].weight = HTree[x].weight + HTree[y].weight;
		HTree[i2].lchild = x;
		HTree[i2].rchild = y;
		HTree[i2].parent = -1;
	}
}

void testHuffman()
{
	cout << "请输入一段字母：" << endl;
	char s[1000] = { '\0' };
	cin >> s;    //输入字符串
	Linklist aa;//定义类Linklist的对象aa
	aa.Construct(s);//统计字符串
	int n = aa.Getlength();//得到哈夫曼树的子树个数
	int*a = new int[n];
	char*b = new char[n];
	Node *v = aa.rear->next->next;
	for (int i = 0; i < n; i++)//初始化哈夫曼树
	{
		a[i] = v->weight;
		b[i] = v->data;
		v = v->next;
	}
	Huffman aaa;//定义Huffman类的对象
	aaa.CreateHTree(a, n);//构建Huffman树
	aaa.CreateTable(b, n);//创建编码表
	cout << "哈弗曼编码表：" << endl;
	cout << "字母" << "\t" << "编码" << "\t" << "权重" << endl;
	for (int ii = 0; ii < n; ii++)//打印编码表
	{
		cout << aaa.HCodeTable[ii].data << "\t" <<
			aaa.HCodeTable[ii].code << "\t" << a[ii] << endl;
	}
	aaa.Encoding(s, n); //编码
	char ss[1000] = { '\0' };
	char d[1000] = { '\0' };
	cout << "请输入一串0和1的编码：" << endl;
	cin >> ss;
	aaa.Decoding(ss, d, n);//译码
}
