#include "Iterator.h"//�����ظ�����

template<class T>
void reverseprint(Chain<T> &c){//�������
	int i, k;
	T *x , *o;
	ListIterator<T> iter;
	x = new T[c.size()];
	o = iter.Initialize(c);
	for (k = 0; o; k++, o = iter.Next()){
		x[k] = *o;
	}
	cout << "���������";
	for (i = k - 1; i >= 0; i--){
		cout << x[i] << " ";
	}
	cout << endl;
}

template <class T>
Chain<T>& merge(Chain<T> &h1, Chain<T> &h2){//�����ϲ�
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
	cout << "��������1��";
	c1.printchain();
	cout << "��������2��";
	c2.printchain();
	cout << "�ϲ�����";
	c3 = merge(c1, c2);//�ϲ�
	c3.printchain();

	Chain<int> ch;
	int a,b;
	cout << "��������-�����볤�ȣ�";
	cin >> a;
	for (int i = 0; i < a; i++){
		cout << "������� " << i + 1 << " ���֣�";
		cin >> b;
		ch.add(b);
	}
	cout << endl;
	cout << "����Ϊ��";
	ch.printchain();//�������
	reverseprint(ch);//�������
	cout << endl;

	while (true){
		cout << "ɾ��Ԫ���밴1��" << endl;
		cout << "��ѯԪ���밴2��" << endl;
		cout << "����Ԫ���밴3��" << endl;
		cout << "����ʵ���밴0��" << endl;
		int select;
		cin >> select;

		switch (select){
		case 0:
			cout << "ʵ�����" << endl;
			system("pause");
			return 0;
		case 1:
			cout << "������Ҫɾ����Ԫ�أ�";
			int a;
			cin >> a;
			ch.erase(a);
			ch.printchain();
			cout << endl;
			break;
		case 2:
			cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
			int b, index;
			cin >> b;
			 index = ch.indexOf(b);
			if (index == -1)//not find
				cout << "û�ҵ���ɾ����Ԫ��" << endl;
			else
				cout << "Ԫ��" << b << "��λ�ã�" << index + 1 << endl;
			cout << endl;
			break;
		case 3:
			int c,d;
			cout << "������Ҫ�����Ԫ�أ�";
			cin >> c;
			cout << "������Ҫ�����λ�ã�";
			cin >> d;
			ch.insert(c, d);
			ch.printchain();
			cout << endl;
			break;
		}
	}
}