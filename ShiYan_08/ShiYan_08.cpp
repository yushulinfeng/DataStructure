#include "stdafx.h"
#include "AdjacencyWGraph.h"

#define MAX_VALUE 999999999

int _tmain(int argc, _TCHAR* argv[]){	
	cout << "----��Ȩ����ͼ----" << endl;
	int nn1, nn2, a1, b1, c1;
	cout << "���뽨������ͼ�Ľڵ����������: ";
	cin >> nn1 >> nn2;
	AdjacencyWGraph<int> graph1(nn1, MAX_VALUE);
	for (int i1 = 1; i1 <= nn2; i1++){
		cout << "�����" << i1 << "������� �յ� Ȩֵ��:  ";
		cin >> a1 >> b1 >> c1;
		graph1.Add(a1, b1, c1);
	}
	cout << "�����������BFS��DFS����㣺" << endl;
	int start;
	cin >> start;
	//����
	cout << "������" << start << "���ڵĽڵ㣺" << endl;
	graph1.Output(start);
	//�����������
	cout << "����������� : " << endl;
	graph1.BFS(start);
	//�����������
	cout << "�������������" << endl; 
	graph1.DFS(start);
	//��ͨ������
	cout << "��������������� " << endl;
	graph1.MakeBFSTree();
	//��С������
	cout << "��С�������� " << endl;
	graph1.Kruskal();

	system("pause");
	return 0;
}
