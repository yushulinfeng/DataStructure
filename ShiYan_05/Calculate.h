#include "stdafx.h"
#include "Stack.cpp"
#include <sstream>

/*计算类*/
class Calculate {
public:
	//计算带括号的算式（例：1+2+(3+4)）
	int calculate(char* input);//（全小写）
private:
	//支持的最大算式长度
	const int MAX_LENGTH = 128;
	//单行单元素无空格四则运算（直接把大一时的Java实验5改了改）
	int jisuan(char* input);
	//局部计算
	int jisuan(char* input, int start, int end);
	//字符串刷新（用算出的值替换括号部分）
	char* replace(char* input, int start, int end,int value);
};