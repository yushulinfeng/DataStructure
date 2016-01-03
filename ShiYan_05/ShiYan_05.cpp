#include "stdafx.h"
#include "Maze.h" 
#include "Electric.h"  

int _tmain(int argc, _TCHAR* argv[]) 
{     
	/*****������-���Գ���*****/
	cout << "--����--" << endl;
	Calculate cal;
	//�޿ո�С��128�ַ���������/0������Ϊ������
	char cal_temp[5][128] = {//������ðٶ���֤�������
		"4+2*3-8/2",//6
		"1+2+(3+(4+(5+6)+7))+8+9",//45 
		"2+3*(4+5)-6/4",//28  
		"6+(9/(8-7)*6+3)-2", //61
		"43+(9+6*(3+5-(96*9-23)+3)-26)+78"//-4 876
	}; 
	for (int i = 0; i < 5; i++){
		cout << cal_temp[i] << "=" 
			<< cal.calculate(cal_temp[i]) << endl;
	}

	/*****�Թ�-���Գ���*****/
	cout << endl << "--�Թ�--" << endl;
	Maze myMaze;    
	bool state =myMaze.FindPath();   
	if (state) 
		myMaze.DrawPath();
	else 
		cout << "�������Թ�·��" << endl;

	/*****��̲���-���Գ���*****/
	cout << endl << "--��·����--" << endl;
	Electric elec;
	state = elec.FindPath(); 
	if (state)
		elec.Output();
	else
		cout << "�����ڲ���·��" << endl;


	return 0;
}


 