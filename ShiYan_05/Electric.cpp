#include "stdafx.h"
#include "Electric.h"
#include<fstream>  

//��ʼ�� һЩ����  
Electric::Electric()//���Թ�����һ��
{
	//��ʼ��maze��ά����  
	grid = new char*[total_row + 2];
	for (int i = 0; i<total_row + 2; ++i)
		grid[i] = new char[total_col + 2];
	//��ʼ��pathShow��ά����  
	pathShow = new char*[total_row + 2];
	for (int i = 0; i<total_row + 2; ++i)
		pathShow[i] = new char[total_col + 2];

	//���ļ���ȡ���ߵĵ�ͼ����  (row=col=10)
	ifstream in("Electric.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	in.close();
	const char* mazeData = strdata.c_str();
	//���������У���ȷ��Ϊ10*10����
	int move = 0;//����\n��\n����鿴�ļ���
	for (int i = 0; i < total_row; i++){
		for (int j = 0; j < total_col; j++)//interesting 0��with down
			grid[i + 1][j + 1] = mazeData[i * 10 + j + move] - '0';//�ÿ�
		move++;
	}

	//���Թ�������һȦ�ϰ���  
	for (int r = 0; r <= total_row + 1; r++)
		grid[0][r] = grid[total_row + 1][r] = 1;
	for (int c = 0; c <= total_col + 1; c++)
		grid[c][0] = grid[c][total_col + 1] = 1;

	offset[0].row = 0; offset[0].col = 1;//��  
	offset[1].row = 1; offset[1].col = 0;//��  
	offset[2].row = 0; offset[2].col = -1;//��  
	offset[3].row = -1; offset[3].col = 0;//��  
	start.row = start_row; 
	start.col = start_col;//���߿�ʼλ��
	finish.row = finish_row; 
	finish.col = finish_col;//����λ��

	cout << "ԭʼͼ��" << endl;
	for (int i = 0; i < total_row + 2; i++) {
		for (int j = 0; j < total_col + 2; j++)
			pathShow[i][j] = grid[i][j];
	}
	pathShow[start_row][start_col] = 2;
	pathShow[finish_row][finish_col] = 3;
	ShowArray(pathShow, total_row + 2, total_col + 2);
}

//���������ά����  
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
	cout << "·������:" << path_length << endl;
	for (int i = 0; i < path_length; i++)
		pathShow[path[i].row][path[i].col] = '+';
	pathShow[start_row][start_col] = 2;
	pathShow[finish_row][finish_col] = 3;
	ShowArray(pathShow, total_row + 2, total_col + 2);
}

//�����㷨  
bool Electric::FindPath()
{
	here.row = start.row;//�ѿ�ʼλ�� ���Ϊ��ǰλ��  
	here.col = start.col;
	grid[start.row][start.col] = 2;//��ʼλ�ñ��  
	while (true){//���������󶼸���·��ֵ
		for (int i = 0; i < 4; i++){//�ѵ�ǰ���ĸ��ھ��еĿ��Ե�λ�ö�������  
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;//��̽��һ��λ��  
			if (grid[neighbour.row][neighbour.col] == 0){//����̽λ�ÿ���  
				grid[neighbour.row][neighbour.col] = grid[here.row][here.col] + 1;//·��ֵ +1  
				if (neighbour.row == finish.row && neighbour.col == finish.col)//����̽�ǽ���λ��  
					break;
				qu_pos.Push(neighbour);//����̽λ�ý�����  
			}
		}
		//�ж��Ƿ񵽴�finish  
		if (neighbour.row == finish.row && neighbour.col == finish.col)
			break;
		if (qu_pos.IsEmpty())
			return false;//��һ���Ĵ�ѭ��֮���Ƕ�����Ԫ�أ���˵���޷����ﲼ���յ�  
		qu_pos.Pop(here);//����̽�ɹ�������е�Ԫ��ȡ�������˵�ǰ��here  
	}

	//��ʽ���������ͼ
	cout << "����ͼ��" << endl;
	for (int i = 0; i<total_row + 2; i++){
		for (int j = 0; j < total_col + 2; j++){
			if (grid[i][j] + 0 < 10)
				cout << grid[i][j] + 0 << "  ";
			else
				cout << grid[i][j] + 0 << " ";
		}
		cout << endl;
	}

	//������ѭ��֮�󣬹���·��  
	path_length = grid[neighbour.row][neighbour.col] - 2;//ʵ�ʵ�·������(��Ϊ֮ǰ����ʼλ��+2)  
	path = new Position[path_length];//��̬����·�����ȿռ�  
	here = finish;//���յ㸳����ǰֵ ��ʼ����Ѱ����С·��  
	for (int j = path_length - 1; j >= 0; j--){
		path[j] = here;//���µ�ǰλ��  
		for (int i = 0; i < 4; i++){
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;//�ٽ�λ��  
			if (grid[neighbour.row][neighbour.col] == j + 2)//�ҵ���һ��λ��
				break;
		} 
		here = neighbour;
	}
	return true;
}