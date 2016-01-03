#include "stdafx.h"
#include "AdjacencyWDigraph.h"

#define INF 999999 ;

//��Ȩ����ͼ
template <class T>
class AdjacencyWGraph : public AdjacencyWDigraph<T>
{
public:
	AdjacencyWGraph(int Vertices = 10, T noEdge = 0) :AdjacencyWDigraph<T>(Vertices, noEdge) {}
	AdjacencyWGraph<T>& Add(int i, int j, const T& w){
		AdjacencyWDigraph<T>::Add(i, j, w);
		AdjacencyWDigraph<T>::a[j][i] = w;
		cout << "a[" << j << "][" << i << "]=" << w << endl;
		return *this;
	}
	AdjacencyWGraph<T>& Delete(int i, int j){
		AdjacencyWDigraph<T>::Delete(i, j);
		AdjacencyWDigraph<T>::a[j][i] = AdjacencyWDigraph<T>::NoEdge;
		return *this;
	}
	int Degree(int i) const { 
		return AdjacencyWDigraph<T>::OutDegree(i); 
	}
	void MakeBFSTree(){//�����������������
		LinkedQueue<int> Q;
		InitializePos();
		int *reach;
		reach = new int[n];
		for (int i = 0; i < n; i++)
			reach[i] = 0;
		reach[1] = 1;
		Q.Add(1);
		while (!Q.IsEmpty()){
			int w;
			Q.Delete(w);
			int u = Begin(w);
			while (u){
				if (reach[u] != 1){
					cout << "(" << w << "," << u << ")" << endl;
					Q.Add(u);
					reach[u] = 1;
				}
				u = NextVertex(w);
			}
		}
		DeactivatePos();
	}
	
	void Kruskal(){
		int* vset;//���ϱ������
		vset=new int[n + 1];
		for (int i = 0; i<=n; i++) 
			vset[i] = i; 
		int k = 0;                    //��С�������ı���
		int j = 0;                    //�������ı���
		int m1, m2,mw, sn1, sn2;
		while (k < n - 1){
			GetMinEdge(m1, m2, mw); //ȡһ����С�ߵ�����������Ȩֵ
			if (mw == NoEdge)break;//�ޱ߿�ѡ��
			sn1 = vset[m1]; //��ȡ�伯�ϱ��
			sn2 = vset[m2]; 
			if (sn1 != sn2){  //���ϲ�ͬ,��������С��������һ����
				cout << "(" << m1 << "," << m2 << "):" << mw << endl;
				k++;
				for (int i = 0; i<n; i++)       //��������ͳһ���
				if (vset[i] == sn2)
					vset[i] = sn1;
			}
			j++;
		}
		if (k == n - 1){//�ɹ�,���ش�����
			cout << endl;
		}else{
			cout << "��������С��������" << endl;
		}
	}

	void GetMinEdge(int &x, int &y, int &w){
		T temp= NoEdge;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (a[i][j] < temp){
					temp = a[i][j];
					x = i; y = j;
				}
			}
		}
		if (temp != NoEdge){
			w = temp;
			a[x][y] = NoEdge;
		}else{
			x = 0; y = 0; w = NoEdge;
		}
	}
};