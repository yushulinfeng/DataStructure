#include "stdafx.h"
#include "Queue.cpp"  

class Electric//��·����  
{
private:
	const int total_row = 10;//ģ������������  
	const int total_col = 10;//����  
	const int start_row = 2;//��ʼ��ֵ  
	const int start_col = 2;//��ʼ��ֵ  
	const int finish_row = 4;//��ֹ��ֵ
	const int finish_col = 6;//��ֹ��ֵ

	Position offset[4];//�ĸ��ƶ�����  
	Position here;//��ǰ����λ��  
	Position neighbour;//��ǰ����Ŀ��ܵ��ھ�λ��  
	Position start;//���߿�ʼλ��  
	Position finish;//���߽���λ��  
	Position *path;//�洢�����·����̬����
	char** grid;//һ��ģ�ⷽ��ľ���  
	char** pathShow;//��ʾ���������  
	int path_length;//���·������  
	Queue<Position> qu_pos;//װ��λ�õĶ��� ���˱�������  
	void ShowArray(char**array, int m, int n);//���m*n�Ķ�ά����  
public:
	Electric();
	~Electric(){};
	void Output();//���·��
	bool FindPath();//Ѱ��·��
};
