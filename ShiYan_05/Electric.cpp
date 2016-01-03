#include "stdafx.h"
#include "Electric.h"
#include<fstream>  

//初始化 一些数据  
Electric::Electric()//与迷宫基本一样
{
	//初始化maze二维数组  
	grid = new char*[total_row + 2];
	for (int i = 0; i<total_row + 2; ++i)
		grid[i] = new char[total_col + 2];
	//初始化pathShow二维数组  
	pathShow = new char*[total_row + 2];
	for (int i = 0; i<total_row + 2; ++i)
		pathShow[i] = new char[total_col + 2];

	//从文件读取布线的地图数据  (row=col=10)
	ifstream in("Electric.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	in.close();
	const char* mazeData = strdata.c_str();
	//导入数组中（请确保为10*10矩阵）
	int move = 0;//处理\n（\n方便查看文件）
	for (int i = 0; i < total_row; i++){
		for (int j = 0; j < total_col; j++)//interesting 0，with down
			grid[i + 1][j + 1] = mazeData[i * 10 + j + move] - '0';//好看
		move++;
	}

	//在迷宫外增加一圈障碍物  
	for (int r = 0; r <= total_row + 1; r++)
		grid[0][r] = grid[total_row + 1][r] = 1;
	for (int c = 0; c <= total_col + 1; c++)
		grid[c][0] = grid[c][total_col + 1] = 1;

	offset[0].row = 0; offset[0].col = 1;//右  
	offset[1].row = 1; offset[1].col = 0;//下  
	offset[2].row = 0; offset[2].col = -1;//左  
	offset[3].row = -1; offset[3].col = 0;//上  
	start.row = start_row; 
	start.col = start_col;//布线开始位置
	finish.row = finish_row; 
	finish.col = finish_col;//结束位置

	cout << "原始图：" << endl;
	for (int i = 0; i < total_row + 2; i++) {
		for (int j = 0; j < total_col + 2; j++)
			pathShow[i][j] = grid[i][j];
	}
	pathShow[start_row][start_col] = 2;
	pathShow[finish_row][finish_col] = 3;
	ShowArray(pathShow, total_row + 2, total_col + 2);
}

//遍历输出二维数组  
void Electric::ShowArray(char**array, int m, int n)
{
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
}


void Electric::Output()
{
	cout << "路径步数:" << path_length << endl;
	for (int i = 0; i < path_length; i++)
		pathShow[path[i].row][path[i].col] = '+';
	pathShow[start_row][start_col] = 2;
	pathShow[finish_row][finish_col] = 3;
	ShowArray(pathShow, total_row + 2, total_col + 2);
}

//布线算法  
bool Electric::FindPath()
{
	here.row = start.row;//把开始位置 标记为当前位置  
	here.col = start.col;
	grid[start.row][start.col] = 2;//起始位置标记  
	while (true){//把整个矩阵都赋上路径值
		for (int i = 0; i < 4; i++){//把当前的四个邻居中的可以的位置都进队列  
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;//试探下一个位置  
			if (grid[neighbour.row][neighbour.col] == 0){//该试探位置可行  
				grid[neighbour.row][neighbour.col] = grid[here.row][here.col] + 1;//路径值 +1  
				if (neighbour.row == finish.row && neighbour.col == finish.col)//该试探是结束位置  
					break;
				qu_pos.Push(neighbour);//把试探位置进队列  
			}
		}
		//判断是否到达finish  
		if (neighbour.row == finish.row && neighbour.col == finish.col)
			break;
		if (qu_pos.IsEmpty())
			return false;//第一次四次循环之后还是队列无元素，则说明无法到达布线终点  
		qu_pos.Pop(here);//把试探成功后进队列的元素取出赋给了当前的here  
	}

	//格式化输出过程图
	cout << "过程图：" << endl;
	for (int i = 0; i<total_row + 2; i++){
		for (int j = 0; j < total_col + 2; j++){
			if (grid[i][j] + 0 < 10)
				cout << grid[i][j] + 0 << "  ";
			else
				cout << grid[i][j] + 0 << " ";
		}
		cout << endl;
	}

	//跳出大循环之后，构造路径  
	path_length = grid[neighbour.row][neighbour.col] - 2;//实际的路径长度(因为之前在起始位置+2)  
	path = new Position[path_length];//动态开辟路径长度空间  
	here = finish;//把终点赋给当前值 开始反向寻找最小路径  
	for (int j = path_length - 1; j >= 0; j--){
		path[j] = here;//记下当前位置  
		for (int i = 0; i < 4; i++){
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;//临近位置  
			if (grid[neighbour.row][neighbour.col] == j + 2)//找到上一个位置
				break;
		} 
		here = neighbour;
	}
	return true;
}