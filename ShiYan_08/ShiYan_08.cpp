#include "stdafx.h"
#include "AdjacencyWGraph.h"

#define MAX_VALUE 999999999

int _tmain(int argc, _TCHAR* argv[]){	
	cout << "----加权无向图----" << endl;
	int nn1, nn2, a1, b1, c1;
	cout << "输入建立无向图的节点个数、边数: ";
	cin >> nn1 >> nn2;
	AdjacencyWGraph<int> graph1(nn1, MAX_VALUE);
	for (int i1 = 1; i1 <= nn2; i1++){
		cout << "输入第" << i1 << "个（起点 终点 权值）:  ";
		cin >> a1 >> b1 >> c1;
		graph1.Add(a1, b1, c1);
	}
	cout << "请输入遍历、BFS、DFS的起点：" << endl;
	int start;
	cin >> start;
	//遍历
	cout << "所有与" << start << "相邻的节点：" << endl;
	graph1.Output(start);
	//宽度优先搜索
	cout << "宽度优先搜索 : " << endl;
	graph1.BFS(start);
	//深度优先搜索
	cout << "深度优先搜索：" << endl; 
	graph1.DFS(start);
	//普通生成树
	cout << "宽度优先生成树： " << endl;
	graph1.MakeBFSTree();
	//最小生成树
	cout << "最小生成树： " << endl;
	graph1.Kruskal();

	system("pause");
	return 0;
}
