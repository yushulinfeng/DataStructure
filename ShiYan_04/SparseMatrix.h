#include "stdafx.h"

/* ϡ�����-����ӳ��*/

//����Ԫ�� ����
template <class T>
class Term
{
public:
	int row, col;
	T data;
};

//ϡ����� �ඨ��
template <class T>
class SparseMatrix
{
public:
	SparseMatrix(int MaxTerms = 5);
	~SparseMatrix(){ delete[]a; }
	void MyTranspose();//ת��(����ı�)
	void MyAdd(SparseMatrix<T> &matrix);//���(����ı�)
	void Append(const Term<T> &t);//���Ԫ��
	void Output(ostream& out)const;
	//���ϵ��������������Ծ�����
	void Transpose(SparseMatrix<T> &matrix)const;//ת��(result=matrix)
	void Add(const SparseMatrix<T> &matrix1, SparseMatrix<T> &matrix2)const;//���(result=matrix2)
private:
	int rows, cols;//����ά��
	int terms;//�����0Ԫ�ظ���
	Term<T> *a;//�������Ԫ�ص�����
	int MaxTerms;//����a�Ĵ�С
};
