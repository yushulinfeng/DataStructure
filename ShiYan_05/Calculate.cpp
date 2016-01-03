#include "stdafx.h"
#include "Calculate.h"

//#include <iostream> 
//using namespace std;//����ר��

//��������ŵ���ʽ����ȷ����ʽ���˴��������쳣��
int Calculate::calculate(char* input){
	Stack<int> sta;
	int j, length = strlen(input);
	for (int i = 1; i <= length; i++){
		if (input[i - 1] == '(')
			sta.Push(i);
		else if (input[i - 1] == ')'){
			try{
				sta.Pop(j);//j,i
				int value = jisuan(input, j, i - 1);//���������е�ֵ
				input = replace(input, j-1, i, value);//��ֵ�滻���Ų��֣��������ţ�
				length = strlen(input);//������ֹ����
				i = j - 1;//����λ��
			}catch (OutOfBounds e){
				//cout << "������ʣ�ࣺ" << j << endl;
			}
		}
	}
	//while (!sta.IsEmpty()){
	//	sta.Delete(j);
	//	cout << "������ʣ�ࣺ" << j << endl;
	//}
	return jisuan(input);
}

//���е�Ԫ���޿ո��������㣨ֱ�ӰѴ�һʱ��Javaʵ��5���˸ģ�
int Calculate::jisuan(char* input){
	int op1 = 0, op2 = 0, result = 0;
	char prev = '+', curr = ' ';
	int index = 0;
	// ��ȡ��һ����������Ϊ�˳�����Ĺ���(��һ��scan.nextInt())
	int op1_temp = 0;
	bool op1_is_neg = false;
	if (input[index] == '-'){
		op1_is_neg = true;//����
		index++;
	}
	do{//talent
		op1 = op1 * 10 + input[index] - 48;
		op1_temp = input[++index];
	} while (op1_temp != '+'&&op1_temp != '-'&&op1_temp != '*'
		&&op1_temp != '/'&&op1_temp != '\0');
	if (op1_is_neg)op1 *= -1;
	//���滹�оͼ�������
	while (input[index] != '\0') {
		curr = input[index++];// �������һ������ôһ���Ƿ���
		//����һ��������
		op2 = 0;
		int op2_temp = 0;
		bool op2_is_neg = false;
		if (input[index] == '-'){
			op2_is_neg = true;//����
			index++;
		}
		do{
			op2 = op2 * 10 + input[index] - 48;
			op2_temp = input[++index];
		} while (op2_temp != '+'&&op2_temp != '-'&&op2_temp != '*'
			&&op2_temp != '/'&&op2_temp != '\0');
		if (op2_is_neg)op2 *= -1;
		/*�����㷨���Ƴټ���*/
		// ����ǳ˳�������㲢����op1
		if (curr == '*' || curr == '/') {
			if (curr == '*') op1 *= op2;
			else if (op2 == 0);//�ݲ�����0�쳣�����������׳����˴��������㣩
			else  op1 /= op2;
		}
		// ��������ǼӼ�
		else if (curr == '+' || curr == '-') {
			// �ж� ��һ�� �Ƿ�Ϊ�ǼӼ���������㲢����result
			if (prev == '+')  result += op1;
			else  result -= op1;
			prev = curr;// prev��curr��ǰһ���������ڸ���
			op1 = op2;// op1��op2��ǰһ��
		}
	}
	// ��Ϊprev��ǰһ��������Ҫ����һ������
	if (prev == '+') result += op1;
	else if (prev == '-') result -= op1;
	// ���ؽ��
	return result;
}

//�ֲ�����
int Calculate::jisuan(char* input, int start, int end){
	//��0��ʼ������start��������end��
	char* temp;
	temp = new char[MAX_LENGTH];
	for (int i = start; i < end; i++){
		temp[i - start] = input[i];
		if ((i - start + 1)!=MAX_LENGTH)
			temp[i - start + 1] = '\0';//���׼�����Ͳ���������ж���
	}
	return jisuan(temp);
}

//�ַ���ˢ�£��������ֵ�滻���Ų��֣�
char*  Calculate::replace(char* input, int start, int end, int value){
	//��0��ʼ������start��������end��
	char *temp, *value_temp;
	temp = new char[MAX_LENGTH];
	value_temp = new char[32];
	for (int i = 0; i < start; i++){
		temp[i] = input[i];
		if ((i + 1) != MAX_LENGTH)
			temp[i + 1] = '\0';//���׼�����Ͳ���������ж���
	}
	//��value������ַ�����char*��//sprintf������ѧϰ����
	stringstream ss;
	ss << value;
	ss >> value_temp;
	int len = strlen(value_temp);
	for (int i = 0; i < len; i++){
		temp[start + i] = value_temp[i];
		if ((start + i + 1) <= MAX_LENGTH)
			temp[start + i + 1] = '\0';
		else 
			break;//�����ݲ�����Խ�����⡣
	}
	//��������
	for (int i = end; i < MAX_LENGTH; i++){
		temp[start + len + i - end] = input[i];
		if ((start + len + i - end + 1) <= MAX_LENGTH)
			temp[start + len + i - end + 1] = '\0';
		else
			break;//�����ݲ�����Խ�����⡣
	}
	return temp;
}