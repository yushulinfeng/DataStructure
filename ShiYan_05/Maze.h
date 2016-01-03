#include "stdafx.h"
#include <fstream>
#include "Calculate.h"//����666����

//Maze�ഴ���Թ���Ѱ�����·��  
class Maze
{
public:
	Maze();
	void ShowArray(char**array, int m, int n);//���m*n�Ķ�ά����  
	bool FindPath();//Ѱ���Թ����ڵķ���  
	void DrawPath();//�����Թ���Ѱ�����  
private:
	const int row = 10, col = 10;//�Թ����  
	Position offset[4];//�������ҵ�ƫ��
	Stack<Position> path;//�洢·���Ķ�ջ  
	char** maze;//�Թ���ͼ������
	char** mazeShow;//��ʾ�Թ�Ѱ�����������  
};