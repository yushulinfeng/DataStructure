#include "stdafx.h"
#include "Calculate.h"

//#include <iostream> 
//using namespace std;//测试专用

//计算带括号的算式（请确保格式，此处不处理异常）
int Calculate::calculate(char* input){
	Stack<int> sta;
	int j, length = strlen(input);
	for (int i = 1; i <= length; i++){
		if (input[i - 1] == '(')
			sta.Push(i);
		else if (input[i - 1] == ')'){
			try{
				sta.Pop(j);//j,i
				int value = jisuan(input, j, i - 1);//计算括号中的值
				input = replace(input, j-1, i, value);//用值替换括号部分（包括括号）
				length = strlen(input);//更新终止条件
				i = j - 1;//更新位置
			}catch (OutOfBounds e){
				//cout << "右括号剩余：" << j << endl;
			}
		}
	}
	//while (!sta.IsEmpty()){
	//	sta.Delete(j);
	//	cout << "左括号剩余：" << j << endl;
	//}
	return jisuan(input);
}

//单行单元素无空格四则运算（直接把大一时的Java实验5改了改）
int Calculate::jisuan(char* input){
	int op1 = 0, op2 = 0, result = 0;
	char prev = '+', curr = ' ';
	int index = 0;
	// 读取第一个数，并作为乘除运算的过渡(就一行scan.nextInt())
	int op1_temp = 0;
	bool op1_is_neg = false;
	if (input[index] == '-'){
		op1_is_neg = true;//负数
		index++;
	}
	do{//talent
		op1 = op1 * 10 + input[index] - 48;
		op1_temp = input[++index];
	} while (op1_temp != '+'&&op1_temp != '-'&&op1_temp != '*'
		&&op1_temp != '/'&&op1_temp != '\0');
	if (op1_is_neg)op1 *= -1;
	//后面还有就继续运算
	while (input[index] != '\0') {
		curr = input[index++];// 如果有下一个，那么一定是符号
		//再下一个是数字
		op2 = 0;
		int op2_temp = 0;
		bool op2_is_neg = false;
		if (input[index] == '-'){
			op2_is_neg = true;//负数
			index++;
		}
		do{
			op2 = op2 * 10 + input[index] - 48;
			op2_temp = input[++index];
		} while (op2_temp != '+'&&op2_temp != '-'&&op2_temp != '*'
			&&op2_temp != '/'&&op2_temp != '\0');
		if (op2_is_neg)op2 *= -1;
		/*核心算法：推迟计算*/
		// 如果是乘除，则计算并存入op1
		if (curr == '*' || curr == '/') {
			if (curr == '*') op1 *= op2;
			else if (op2 == 0);//暂不处理0异常，建议向上抛出（此处忽略运算）
			else  op1 /= op2;
		}
		// 否则，如果是加减
		else if (curr == '+' || curr == '-') {
			// 判断 上一步 是否为是加减，是则计算并存入result
			if (prev == '+')  result += op1;
			else  result -= op1;
			prev = curr;// prev比curr靠前一步，类似于跟随
			op1 = op2;// op1比op2靠前一步
		}
	}
	// 因为prev靠前一步，所以要将这一步补上
	if (prev == '+') result += op1;
	else if (prev == '-') result -= op1;
	// 返回结果
	return result;
}

//局部计算
int Calculate::jisuan(char* input, int start, int end){
	//从0开始，包含start，不包含end。
	char* temp;
	temp = new char[MAX_LENGTH];
	for (int i = start; i < end; i++){
		temp[i - start] = input[i];
		if ((i - start + 1)!=MAX_LENGTH)
			temp[i - start + 1] = '\0';//多点准备，就不必最后再判断了
	}
	return jisuan(temp);
}

//字符串刷新（用算出的值替换括号部分）
char*  Calculate::replace(char* input, int start, int end, int value){
	//从0开始，包含start，不包含end。
	char *temp, *value_temp;
	temp = new char[MAX_LENGTH];
	value_temp = new char[32];
	for (int i = 0; i < start; i++){
		temp[i] = input[i];
		if ((i + 1) != MAX_LENGTH)
			temp[i + 1] = '\0';//多点准备，就不必最后再判断了
	}
	//将value处理成字符串（char*）//sprintf不方便学习讨论
	stringstream ss;
	ss << value;
	ss >> value_temp;
	int len = strlen(value_temp);
	for (int i = 0; i < len; i++){
		temp[start + i] = value_temp[i];
		if ((start + i + 1) <= MAX_LENGTH)
			temp[start + i + 1] = '\0';
		else 
			break;//这里暂不处理越界问题。
	}
	//后续部分
	for (int i = end; i < MAX_LENGTH; i++){
		temp[start + len + i - end] = input[i];
		if ((start + len + i - end + 1) <= MAX_LENGTH)
			temp[start + len + i - end + 1] = '\0';
		else
			break;//这里暂不处理越界问题。
	}
	return temp;
}