#include "Iterator.h"//不必重复包含

template<class T>
void reverseprint(Chain<T> &c){//逆序输出
	int i, k;
	T *x , *o;
	ListIterator<T> iter;
	x = new T[c.size()];
	o = iter.Initialize(c);
	for (k = 0; o; k++, o = iter.Next()){
		x[k] = *o;
	}
	cout << "逆序输出：";
	for (i = k - 1; i >= 0; i--){
		cout << x[i] << " ";
	}
	cout << endl;
}

template <class T>
Chain<T>& merge(Chain<T> &h1, Chain<T> &h2){//有序表合并
	Chain<T> head;
	ListIterator<T> i1, i2;
	T *o1, *o1_temp, *o2, *o2_temp;
	o1 = i1.Initialize(h1);
	o2 = i2.Initialize(h2);
	for (int i = 0; i < h1.size() + h2.size(); i++){
		if (*o1 >= *o2){
			if (*o1 == *o2){
				o1_temp = i1.Next(); 
				if (o1_temp) *o1 = *o1_temp;
				else *o1 = -1;
			}else{
				head.add(*o1); 
				o1_temp = i1.Next();
				if (o1_temp) *o1 = *o1_temp;
				else *o1 = -1;//another
			}
		}else{
			head.add(*o2);
			o2_temp = i2.Next();
			if (o2_temp) *o2 = *o2_temp;
			else *o2 = -1;
		}
	}
	return head;
}

int main(){
	Chain<int> c1, c2, c3;
	c1.add(1);c1.add(3);c1.add(5);
	c2.add(2);c2.add(3);c2.add(6);
	cout << "有序链表1：";
	c1.printchain();
	cout << "有序链表2：";
	c2.printchain();
	cout << "合并链表：";
	c3 = merge(c1, c2);//合并
	c3.printchain();

	Chain<int> ch;
	int a,b;
	cout << "创建链表-请输入长度：";
	cin >> a;
	for (int i = 0; i < a; i++){
		cout << "请输入第 " << i + 1 << " 数字：";
		cin >> b;
		ch.add(b);
	}
	cout << endl;
	cout << "链表为：";
	ch.printchain();//输出链表
	reverseprint(ch);//逆序输出
	cout << endl;

	while (true){
		cout << "删除元素请按1：" << endl;
		cout << "查询元素请按2：" << endl;
		cout << "插入元素请按3：" << endl;
		cout << "结束实验请按0：" << endl;
		int select;
		cin >> select;

		switch (select){
		case 0:
			cout << "实验结束" << endl;
			system("pause");
			return 0;
		case 1:
			cout << "请输入要删除的元素：";
			int a;
			cin >> a;
			ch.erase(a);
			ch.printchain();
			cout << endl;
			break;
		case 2:
			cout << "请输入要查找的元素：" << endl;
			int b, index;
			cin >> b;
			 index = ch.indexOf(b);
			if (index == -1)//not find
				cout << "没找到可删除的元素" << endl;
			else
				cout << "元素" << b << "的位置：" << index + 1 << endl;
			cout << endl;
			break;
		case 3:
			int c,d;
			cout << "请输入要插入的元素：";
			cin >> c;
			cout << "请输入要插入的位置：";
			cin >> d;
			ch.insert(c, d);
			ch.printchain();
			cout << endl;
			break;
		}
	}
}