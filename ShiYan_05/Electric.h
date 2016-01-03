#include "stdafx.h"
#include "Queue.cpp"  

class Electric//电路布线  
{
private:
	const int total_row = 10;//模拟矩阵的总行数  
	const int total_col = 10;//列数  
	const int start_row = 2;//起始行值  
	const int start_col = 2;//起始列值  
	const int finish_row = 4;//终止行值
	const int finish_col = 6;//终止列值

	Position offset[4];//四个移动方向  
	Position here;//当前矩阵位置  
	Position neighbour;//当前矩阵的可能的邻居位置  
	Position start;//布线开始位置  
	Position finish;//布线结束位置  
	Position *path;//存储的最短路径动态数组
	char** grid;//一个模拟方格的矩阵  
	char** pathShow;//显示结果的数组  
	int path_length;//最短路径步数  
	Queue<Position> qu_pos;//装载位置的队列 靠此遍历方格  
	void ShowArray(char**array, int m, int n);//输出m*n的二维数组  
public:
	Electric();
	~Electric(){};
	void Output();//输出路径
	bool FindPath();//寻求路径
};
