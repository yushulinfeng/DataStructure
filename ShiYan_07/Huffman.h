#include "stdafx.h"
#include<cstdio>
#include<cstring>
#include<cstdlib>

//�������ڵ�
struct node{
	int weight;//�϶�Ϊint
	struct node *p;//��
	struct node *l;//��
	struct node *r;//��
	node():p(NULL),l(NULL),r(NULL),weight(NULL){
	}
	node(struct node *n) 
		:p(n->p), l(n->l), r(n->r), weight(n->weight){
	}
};

class HuffmanCode{
public:
	HuffmanCode(int* input, int length);
	void PreOrder(){ PreOrder(huffmantree); }
	void MidOrder(){ MidOrder(huffmantree); }
	void PrintCode(){ PrintCode(huffmantree); }
private:
	int size;
	int* mark;
	struct node**  huffman;
	struct node*  huffmantree;
	void Initialize(); 
	void Choose(int *choose); //ѡ����С����С�Ľڵ�
	void PrintCode(struct node *T);
	void PreOrder(struct node *T);
	void MidOrder(struct node *T);
	void PrintNode(struct node *node){ cout << node->weight << " "; }
};

HuffmanCode::HuffmanCode(int* input, int length){
	if (length > 100){
		cout << "OutOfBounds" << endl;
		return;
	}
	mark = new int[100];
	huffman = new node*[100];
	for (int i = 0; i < 100; i++) 
		mark[i] = 0;
	size = length;
	for (int i = 0; i < length; i++) {
		huffman[i] = new node();
		huffman[i]->weight = input[i];
	}
	Initialize();
}

void HuffmanCode::PreOrder(struct node *T){
	if (T){
		PrintNode(T);
		PreOrder(T->l);
		PreOrder(T->r);
	}
}

void HuffmanCode::MidOrder(struct node *T){
	if (T){
		MidOrder(T->l);
		PrintNode(T);
		MidOrder(T->r);
	}
}

void HuffmanCode::PrintCode(struct node *T){
	if (T->l||T->r){//��Ҷ�ӽڵ㣬�����ݹ�
		if (T->l){
			T->l->p = T;//��һ������һ���硭����ʱ��ʼ�����ڵ�
			PrintCode(T->l);
		}
		if (T->r){
			T->r->p = T;
			PrintCode(T->r);
		}
	}else{
		if (T == NULL)return;
		int *arrays=new int[100];
		int index = 0;
		struct node *temp=T;
		while (temp->p){
			if (temp->p->l)//���������ڣ����жϵ�ǰ�Ƿ�λ������������ַ�Ƿ�һ�£���ΪȨֵ���ظ���
				arrays[index++] = ((temp) == (temp->p->l)) ? 0 : 1;
			else//û�����������϶���������
				arrays[index++] = 1;
			temp = temp->p;
		}
		cout << T->weight << " : ";
		for (int i = index-1; i >= 0; i--) 
			cout << arrays[i] << " ";//�������
		cout << endl;
	}
}
//ѡ����С�ġ��ڶ�С�������ڵ�
void HuffmanCode::Choose( int *choose){
	int i = 0, temp = 0;
	int minkey = 0, tkey = 0;
	//�ҵ���һ��δ��ǵ�λ��
	for (; i < size; i++){
		if (!mark[i]){
			minkey = i;
			i++;
			break;
		}
	}
	tkey = minkey;
	for (; i < size; i++){
		if (!mark[i]){
			//�ڶ���δ��ǵ�λ�ã�ֻ���״ε��˲���true��
			if (tkey == minkey)
				tkey = i;
			//����Сֵ����Сֵ
			if (huffman[i]->weight < huffman[minkey]->weight){
				tkey = minkey;
				minkey = i;
			}
			//���������first mark=min��
			if (huffman[i]->weight < huffman[tkey]->weight  && i != minkey){
				tkey = i;
			}
		}
	}
	choose[0] = minkey;
	choose[1] = tkey;
}

void HuffmanCode::Initialize(){
	int choose[2];
	int i;
	struct node *mynode = new node();
	for (i = 0; i < size - 1; i++){
		//ѡ����С�ġ��ڶ�С�������ڵ�
		Choose(choose);
		//�ϲ��������ڵ�
		mynode = new node();
		mynode->weight = huffman[choose[0]]->weight + huffman[choose[1]]->weight;//����keyֵ
		mynode->l = new node(huffman[choose[0]]);
		mynode->r = huffman[choose[1]];
		//ˢ�½ڵ����飨���µĽڵ��滻��С�Ľڵ㣬���ڶ�С�Ľڵ������ʹ�õı�ǣ�
		//��ʵ���൱�ڼ����µĽڵ㣬ɾȥ�ɵĽڵ�
		huffman[choose[0]] = mynode;
		mark[choose[1]] = 1;
	}
	huffmantree = huffman[choose[0]];
}
