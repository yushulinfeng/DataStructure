#include "stdafx.h"
#include "LinkedQueue.h"

//加权有向图
template <class T>
class AdjacencyWDigraph
{
public:
	AdjacencyWDigraph(int Vertices = 10, T noEdge = 0);
	virtual ~AdjacencyWDigraph() { Delete2DArray(a, n + 1); }
	AdjacencyWDigraph<T>& Add(int i, int j, const T& w);
	AdjacencyWDigraph<T>& Delete(int i, int j);
	//基本数据
	bool Exist(int i, int j) const;
	int OutDegree(int i) const;
	int InDegree(int i) const;
	int Edges() const { return e; }
	int Vertices() const { return n; }
	//遍历
	void Output(int i);
	//宽度优先搜索
	void BFS(int v);
	//深度优先搜索
	void DFS(int v);
protected:
	T NoEdge;
	int n;
	int e;
	T **a;
	int *pos;
	void Init2DArray(T ** &x, int rows, int cols);
	void Delete2DArray(T ** &x, int rows);
	int Begin(int i);
	int NextVertex(int i);
	void InitializePos() { pos = new int[n + 1]; }
	void DeactivatePos() { delete[] pos; }
	void dfs(int v, int reach[], int label);
};

template <class T>
AdjacencyWDigraph<T>::AdjacencyWDigraph(int Vertices, T noEdge){
	n = Vertices;
	e = 0;
	NoEdge = noEdge;
	Init2DArray(a, n + 1, n + 1);
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
		a[i][j] = NoEdge;
}

template <class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const{
	if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge)
		return false;
	return true;
}

template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Add(int i, int j, const T&w)
{
	if (i<1 || j<1 || i>n || j>n || i == j || a[i][j] != NoEdge)
		throw OutOfBounds();
	a[i][j] = w;
	e++;
	cout << "a[" << i << "][" << j << "]=" << a[i][j] << endl;
	return *this;
}

template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Delete(int i, int j){
	if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge)
		throw BadInput();
	a[i][j] = NoEdge;
	e--;
	return *this;
}

template <class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const{
	if (i<1 || i>n)
		throw OutOfBounds();
	int sum = 0;
	for (int j = 1; j <= n; j++)
	if (a[i][j] != NoEdge)
		sum++;
	return sum;
}

template <class T>
int AdjacencyWDigraph<T>::InDegree(int i) const{
	if (i<1 || i>n) throw BadInput();
	int sum = 0;
	for (int j = 1; j <= n; j++)
	if (a[j][i] != NoEdge)
		sum++;
	return sum;
}

template <class T>
void AdjacencyWDigraph<T>::Init2DArray(T ** &x, int rows, int cols){
	x = new T *[rows];
	for (int i = 0; i<rows; i++)
		x[i] = new int[cols];
}

template <class T>
void AdjacencyWDigraph<T>::Delete2DArray(T ** &x, int rows){
	for (int i = 0; i<rows; i++)
		delete[] x[i];
	delete[] x;
	x = 0;
}

//遍历
template <class T>
void AdjacencyWDigraph<T>::Output(int i){
	InitializePos();
	int  x = Begin(i);
	while (x != 0){
		cout << x << " ";
		x = NextVertex(i);
	}
	cout << endl;
}

template <class T>
int AdjacencyWDigraph<T>::Begin(int i){
	if (i<1 || i>n)
		throw OutOfBounds();
	for (int j = 1; j <= n; j++)
	if (a[i][j] != NoEdge){
		pos[i] = j;
		return j;
	}
	pos[i] = n + 1;
	return 0;
}

template <class T>
int AdjacencyWDigraph<T>::NextVertex(int i){
	if (i<1 || i>n)
		throw OutOfBounds();
	for (int j = pos[i] + 1; j <= n; j++)
	if (a[i][j] != NoEdge){
		pos[i] = j;
		return j;
	}
	pos[i] = n + 1;
	return 0;
}

//宽度优先搜索
template <class T>
void AdjacencyWDigraph<T>::BFS(int v){
	LinkedQueue<int> Q;
	InitializePos();
	int *reach;
	reach = new int[n];
	for (int i = 0; i < n; i++)
		reach[i] = 0;
	reach[v] = 1;
	Q.Add(v);
	while (!Q.IsEmpty()){
		int w;
		Q.Delete(w);
		cout << w << " ";
		int u = Begin(w);
		while (u){
			if (reach[u] != 1){
				Q.Add(u);
				reach[u] = 1;
			}
			u = NextVertex(w);
		}
	}
	cout << endl;
	DeactivatePos();
}

//深度优先搜索
template <class T>
void AdjacencyWDigraph<T>::DFS(int v){
	InitializePos();
	int *reach;
	reach = new int[n];
	for (int i = 0; i < n; i++)
		reach[i] = 0;
	dfs(v, reach, 1);//搜索
	cout << endl;
	DeactivatePos();
}

template <class T>
void AdjacencyWDigraph<T>::dfs(int v, int reach[], int label){
	cout << v << " ";
	reach[v] = label;
	int u = Begin(v);
	while (u){
		if (reach[u] != label)
			dfs(u, reach, label);
		u = NextVertex(v);
	}
}