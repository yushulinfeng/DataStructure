#include "stdafx.h"
#include "Maze.h"

//�Թ����ݵ������ƫ�����ĳ�ʼ��  
Maze::Maze()
{
	//��ʼ��maze��ά����  
	maze = new char*[row + 2];
	for (int i = 0; i<row + 2; ++i)
		maze[i] = new char[col + 2];
	//��ʼ��mazeShow��ά����  
	mazeShow = new char*[row + 2];
	for (int i = 0; i<row + 2; ++i)
		mazeShow[i] = new char[col + 2];
	//��ƫ�������г�ʼ��  
	offset[0].row = 0;  offset[0].col = 1;  //����  
	offset[1].row = 1;  offset[1].col = 0;  //����  
	offset[2].row = 0;  offset[2].col = -1; //����  
	offset[3].row = -1; offset[3].col = 0;  //����  
	//���ļ���ȡ�Թ��ĵ�ͼ����  (row=col=10)
	ifstream in("Maze.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	in.close();
	const char* mazeData = strdata.c_str();
	//���Թ����ݵ����Թ������У���ȷ��Ϊ10*10����
	int move = 0;//����\n��\n����鿴�ļ���
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)//interesting 0��with down
			maze[i + 1][j + 1] = mazeData[i * 10 + j + move] - '0';//�ÿ�
		move++;
	}
	//���Թ�������һȦ�ϰ���  
	for (int r = 0; r <= row + 1; r++)
		maze[0][r] = maze[row + 1][r] = 1;
	for (int c = 0; c <= col + 1; c++)
		maze[c][0] = maze[c][col + 1] = 1;
	for (int i = 0; i < row + 2; i++){
		for (int j = 0; j < col + 2; j++)
			mazeShow[i][j] = maze[i][j];
	}
	cout <<  "ԭʼ��ͼ��" << endl;
	ShowArray(maze, row + 2, col + 2);
}

//���������ά����  
void Maze::ShowArray(char**array, int m, int n)
{
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++) 
			cout << array[i][j] << " ";
		cout << endl;
	}
}
 
//Ѱ�Ҵ�λ��(1��1)������(m,m)��·��  
//����ɹ���true�����򷵻�false  
bool Maze::FindPath()
{
	Position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;
	int option = 0;     //ѡ����ƶ�����  
	int LastOption = 3; //���һ������ѡ��  
	//Ѱ��һ��·��  
	while (here.row != row || here.col != col)//���ǳ���
	{
		//Ѱ�Ҳ����ƶ���һ�����ڵ�λ��  
		int r, c;
		while (option <= LastOption){//���α���ÿ������
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)//��δ�߹���·�����ɽ���˷���
				break;
			option++;
		}
		//�Ƿ��ҵ�һ�����ڵ�λ��  
		if (option <= LastOption)//��һ��break�ģ�����·
		{
			//�ƶ���maze[r][c]  
			//����ǰλ��ѹ���ջ  
			path.Push(here);
			here.row = r;
			here.col = c;
			//�����ϰ�������ֹ�ٴη���  
			maze[r][c] = 4;//�ϰ����
			option = 0;
		}else{
			//û�п��õ�����λ�ã���һ��ѭ��û��break������·�ˣ�
			//������һ���ڵ�
			if (path.IsEmpty())//ջ�գ����ص����������·��������·��
				return false;
			Position next ;
			path.Pop(next);//ȥ��һ��
			option = 0;
			here = next;
		}
	}
	return true;
}


//�������յ�Ѱ�����  
void Maze::DrawPath()
{
	Position temp;
	while (!path.IsEmpty())
	{
		path.Pop(temp);//��ջ��ȡ��λ�ã����������Ӧλ��
		mazeShow[temp.row][temp.col] = '+';//·�߱��
	}
	mazeShow[row][col] = 3;//�յ���
	mazeShow[1][1] = 2;//�����
	cout <<  "�����ͼ��" << endl;
	ShowArray(mazeShow, row + 2, col + 2);
}
