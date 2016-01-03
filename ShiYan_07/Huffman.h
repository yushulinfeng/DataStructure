#include "stdafx.h"
#include<cstdio>
#include<cstring>
#include<cstdlib>

//哈夫曼节点
struct node{
	int weight;//肯定为int
	struct node *p;//父
	struct node *l;//左
	struct node *r;//右
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
	void Choose(int *choose); //选出最小、次小的节点
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
	if (T->l||T->r){//非叶子节点，继续递归
		if (T->l){
			T->l->p = T;//这一行想了一下午……即时初始化父节点
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
			if (temp->p->l)//左子树存在，则判断当前是否位于左子树（地址是否一致，因为权值可重复）
				arrays[index++] = ((temp) == (temp->p->l)) ? 0 : 1;
			else//没有左子树，肯定在右子树
				arrays[index++] = 1;
			temp = temp->p;
		}
		cout << T->weight << " : ";
		for (int i = index-1; i >= 0; i--) 
			cout << arrays[i] << " ";//逆序输出
		cout << endl;
	}
}
//选出最小的、第二小的两个节点
void HuffmanCode::Choose( int *choose){
	int i = 0, temp = 0;
	int minkey = 0, tkey = 0;
	//找到第一个未标记的位置
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
			//第二个未标记的位置（只有首次到此才是true）
			if (tkey == minkey)
				tkey = i;
			//找最小值、次小值
			if (huffman[i]->weight < huffman[minkey]->weight){
				tkey = minkey;
				minkey = i;
			}
			//特殊情况（first mark=min）
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
		//选出最小的、第二小的两个节点
		Choose(choose);
		//合并这两个节点
		mynode = new node();
		mynode->weight = huffman[choose[0]]->weight + huffman[choose[1]]->weight;//更新key值
		mynode->l = new node(huffman[choose[0]]);
		mynode->r = huffman[choose[1]];
		//刷新节点数组（用新的节点替换最小的节点，将第二小的节点添加已使用的标记）
		//其实就相当于加了新的节点，删去旧的节点
		huffman[choose[0]] = mynode;
		mark[choose[1]] = 1;
	}
	huffmantree = huffman[choose[0]];
}
