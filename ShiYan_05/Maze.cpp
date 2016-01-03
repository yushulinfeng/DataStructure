#include "stdafx.h"
#include "Maze.h"

//迷宫数据的输入和偏移量的初始化  
Maze::Maze()
{
	//初始化maze二维数组  
	maze = new char*[row + 2];
	for (int i = 0; i<row + 2; ++i)
		maze[i] = new char[col + 2];
	//初始化mazeShow二维数组  
	mazeShow = new char*[row + 2];
	for (int i = 0; i<row + 2; ++i)
		mazeShow[i] = new char[col + 2];
	//对偏移量进行初始化  
	offset[0].row = 0;  offset[0].col = 1;  //向右  
	offset[1].row = 1;  offset[1].col = 0;  //向下  
	offset[2].row = 0;  offset[2].col = -1; //向左  
	offset[3].row = -1; offset[3].col = 0;  //向上  
	//从文件读取迷宫的地图数据  (row=col=10)
	ifstream in("Maze.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	in.close();
	const char* mazeData = strdata.c_str();
	//将迷宫数据导入迷宫数组中（请确保为10*10矩阵）
	int move = 0;//处理\n（\n方便查看文件）
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)//interesting 0，with down
			maze[i + 1][j + 1] = mazeData[i * 10 + j + move] - '0';//好看
		move++;
	}
	//在迷宫外增加一圈障碍物  
	for (int r = 0; r <= row + 1; r++)
		maze[0][r] = maze[row + 1][r] = 1;
	for (int c = 0; c <= col + 1; c++)
		maze[c][0] = maze[c][col + 1] = 1;
	for (int i = 0; i < row + 2; i++){
		for (int j = 0; j < col + 2; j++)
			mazeShow[i][j] = maze[i][j];
	}
	cout <<  "原始地图：" << endl;
	ShowArray(maze, row + 2, col + 2);
}

//遍历输出二维数组  
void Maze::ShowArray(char**array, int m, int n)
{
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++) 
			cout << array[i][j] << " ";
		cout << endl;
	}
}
 
//寻找从位置(1，1)到出口(m,m)的路径  
//如果成功则true，否则返回false  
bool Maze::FindPath()
{
	Position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;
	int option = 0;     //选择的移动方向  
	int LastOption = 3; //最后一个方向选择  
	//寻找一条路径  
	while (here.row != row || here.col != col)//不是出口
	{
		//寻找并且移动到一个相邻的位置  
		int r, c;
		while (option <= LastOption){//依次遍历每个方向
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)//是未走过的路，即可进入此方向
				break;
			option++;
		}
		//是否找到一个相邻的位置  
		if (option <= LastOption)//上一步break的，即有路
		{
			//移动到maze[r][c]  
			//将当前位置压入堆栈  
			path.Push(here);
			here.row = r;
			here.col = c;
			//设置障碍物以阻止再次访问  
			maze[r][c] = 4;//障碍标记
			option = 0;
		}else{
			//没有可用的相邻位置（上一步循环没有break，即无路了）
			//回溯上一个节点
			if (path.IsEmpty())//栈空，即回到了起点仍无路，就是无路了
				return false;
			Position next ;
			path.Pop(next);//去上一步
			option = 0;
			here = next;
		}
	}
	return true;
}


//绘制最终的寻径结果  
void Maze::DrawPath()
{
	Position temp;
	while (!path.IsEmpty())
	{
		path.Pop(temp);//从栈中取出位置，存入数组对应位置
		mazeShow[temp.row][temp.col] = '+';//路线标记
	}
	mazeShow[row][col] = 3;//终点标记
	mazeShow[1][1] = 2;//起点标记
	cout <<  "结果地图：" << endl;
	ShowArray(mazeShow, row + 2, col + 2);
}
