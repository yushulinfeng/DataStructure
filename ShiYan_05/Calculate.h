#include "stdafx.h"
#include "Stack.cpp"
#include <sstream>

/*������*/
class Calculate {
public:
	//��������ŵ���ʽ������1+2+(3+4)��
	int calculate(char* input);//��ȫСд��
private:
	//֧�ֵ������ʽ����
	const int MAX_LENGTH = 128;
	//���е�Ԫ���޿ո��������㣨ֱ�ӰѴ�һʱ��Javaʵ��5���˸ģ�
	int jisuan(char* input);
	//�ֲ�����
	int jisuan(char* input, int start, int end);
	//�ַ���ˢ�£��������ֵ�滻���Ų��֣�
	char* replace(char* input, int start, int end,int value);
};