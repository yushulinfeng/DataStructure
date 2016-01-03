#include "stdafx.h"
#include "Maze.h" 
#include "Electric.h"  

int _tmain(int argc, _TCHAR* argv[]) 
{     
	/*****计算器-测试程序*****/
	cout << "--运算--" << endl;
	Calculate cal;
	//无空格小于128字符，除法无/0，精度为整数级
	char cal_temp[5][128] = {//网络好用百度验证结果更快
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

	/*****迷宫-测试程序*****/
	cout << endl << "--迷宫--" << endl;
	Maze myMaze;    
	bool state =myMaze.FindPath();   
	if (state) 
		myMaze.DrawPath();
	else 
		cout << "不存在迷宫路径" << endl;

	/*****最短布线-测试程序*****/
	cout << endl << "--电路布线--" << endl;
	Electric elec;
	state = elec.FindPath(); 
	if (state)
		elec.Output();
	else
		cout << "不存在布线路径" << endl;


	return 0;
}


 