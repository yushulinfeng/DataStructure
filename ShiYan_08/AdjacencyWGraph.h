#include "stdafx.h"
#include "AdjacencyWDigraph.h"

#define INF 999999 ;

//加权无向图
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
	void MakeBFSTree(){//宽度优先搜索生成树
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
		int* vset;//集合编号数组
		vset=new int[n + 1];
		for (int i = 0; i<=n; i++) 
			vset[i] = i; 
		int k = 0;                    //最小生成树的边数
		int j = 0;                    //遍历过的边数
		int m1, m2,mw, sn1, sn2;
		while (k < n - 1){
			GetMinEdge(m1, m2, mw); //取一条最小边的两个顶点与权值
			if (mw == NoEdge)break;//无边可选了
			sn1 = vset[m1]; //获取其集合编号
			sn2 = vset[m2]; 
			if (sn1 != sn2){  //集合不同,则这是最小生成树的一条边
				cout << "(" << m1 << "," << m2 << "):" << mw << endl;
				k++;
				for (int i = 0; i<n; i++)       //两个集合统一编号
				if (vset[i] == sn2)
					vset[i] = sn1;
			}
			j++;
		}
		if (k == n - 1){//成功,不必处理了
			cout << endl;
		}else{
			cout << "不存在最小生成树。" << endl;
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