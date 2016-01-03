#include "stdafx.h"
#include <fstream>
#include "Calculate.h"//……666……

//Maze类创建迷宫并寻找最短路径  
class Maze
{
public:
	Maze();
	void ShowArray(char**array, int m, int n);//输出m*n的二维数组  
	bool FindPath();//寻找迷宫出口的方法  
	void DrawPath();//绘制迷宫的寻径结果  
private:
	const int row = 10, col = 10;//迷宫宽高  
	Position offset[4];//上下左右的偏移
	Stack<Position> path;//存储路径的堆栈  
	char** maze;//迷宫地图的数组
	char** mazeShow;//显示迷宫寻径结果的数组  
};