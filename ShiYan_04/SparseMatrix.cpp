#include "stdafx.h"
#include "SparseMatrix.h"

//ϡ�����Ĺ��캯��
template <class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	if (maxTerms < 1){
		throw BadInitializers();
		return;
	}
	MaxTerms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = 0;//��Ԫ����
	rows = cols = maxTerms;//����=����=���Ԫ���������˷�һ����Դ�ɡ�
}

//ʵ��Append���������һ��Ԫ��
template<class T>
void SparseMatrix<T>::Append(const Term<T> & t)
{
	//��һ������Ԫ����ӵ�*this��
	if (terms >= MaxTerms){
		throw NOMEM();
		return;
	}
	//�ظ��������ֵ
	bool need_add = true;
	for (int i = 0; i < terms; i++){
		if (a[i].row == t.row&&a[i].col == t.col){
			a[i] = t;
			need_add = false;
		}
	}
	if (need_add){
		a[terms] = t;
		terms++;
	}
}

//ʵ��ת�÷���������ÿ��Ԫ�ص�row,col
template<class T>
void SparseMatrix<T> ::MyTranspose() 
{
	for (int i = 0; i < terms; i++){
		int temp = a[i].col;
		a[i].col = a[i].row;
		a[i].row = temp;
	}
}

//ʵ����ӷ��������¾���ӵ�ԭ���ľ���
template<class T>
void SparseMatrix<T> ::MyAdd(SparseMatrix<T> &matrix){
	for (int j = 0; j < matrix.terms; j++){//����ж��¾����е�Ԫ��
		bool need_add = true;
		for (int i = 0; i < terms; i++){//���ԭ�������У������
			if (a[i].row == matrix.a[j].row&&a[i].col == matrix.a[j].col){
				a[i].data += matrix.a[j].data;
				need_add = false;
			}
		}
		if (need_add){//û�У������
			a[terms] = matrix.a[j];
			terms++;
		}
	}
}

//ʵ��Output����
template<class T>
void SparseMatrix<T>::Output(ostream& out)const
{
	for (int i = 0; i < terms; i++)
		out << "a(" << a[i].row << "," << a[i].col << ")=" << a[i].data << endl;
}

//����<<
template<class T>
ostream& operator<<(ostream &out, SparseMatrix<T> &x)
{
	x.Output(out);
	return out;
}

////////////////////////////////////////////�α��ϵķ������ײ����

//ʵ��ת�÷���
template<class T>
void SparseMatrix<T> ::Transpose(SparseMatrix<T> &matrix)const
{
	//��*this��ת�ý������matrix
	//matrix���Ƿ����㹻�ռ�
	if (terms > matrix.MaxTerms)
		throw NOMEM();
	matrix.cols = rows;
	matrix.rows = cols;
	matrix.terms = terms;
	//ColSize[]:ÿ���ֵķ���Ԫ����   RowNext[]��ת�ú�ÿ���з���Ԫ����matrix�е���һ��λ�õ��±�
	int *ColSize, *RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[rows + 1];
	//��ʼ��ColSize
	for (int i = 1; i < cols; i++)
	{
		ColSize[i] = 0;
	}
	//����*thisÿ���з���Ԫ�ظ���
	for (int i = 0; i < terms; i++)
	{
		ColSize[a[i].col]++;
	}
	//����matrix��ÿһ�е���ʼ��
	RowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
	{
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	}

	//ִ��ת�ò���
	for (int i = 0; i < terms; i++)
	{
		int j = RowNext[a[i].col]++;
		matrix.a[j].row = a[i].col;
		matrix.a[j].col = a[i].row;
		matrix.a[j].data = a[i].data;
	}
}

//ʵ��Add���� �������ϡ��������
template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &matrix1, SparseMatrix<T> &matrix2)const
{ //matrix2 = *this + matrix1
	if (rows != matrix1.rows || cols != matrix1.cols)
		throw SizeMismatch();
	matrix2.rows = rows;
	matrix2.cols = cols;
	matrix2.terms = 0;
	//����*this��matrix1���α�
	int pt = 0;
	int pm = 0;
	//��*this��matrix1�б���
	while (pt < terms&&pm < matrix1.terms)
	{
		//ÿһ��Ԫ�ص���������
		int indt = a[pt].row*cols + a[pt].col;
		int indm = matrix1.a[pm].row*cols + matrix1.a[pm].col;
		if (indt >indm)
		{//matrix1��Ԫ���ں�
			matrix2.Append(a[pt]);
			pt++;
		}
		else
		{
			if (indt == indm)
			{//λ����ͬ
				//�����Ͳ�Ϊ�����ӵ�matrix2��
				if (a[pt].data + matrix1.a[pm].data)
				{
					Term<T> t;
					t.row = a[pt].row;
					t.col = a[pt].col;
					t.data = a[pt].data + matrix1.a[pm].data;
					matrix2.Append(t);
				}
				pt++;
				pm++;
			}
			else
			{
				//��matrix1�е���һ��Ԫ����ӵ�matrix2��
				matrix2.Append(matrix1.a[pm]);
				pm++;
			}
		}
	}

	//����ʣ��Ԫ��
	for (; pt < terms; pt++)
		matrix2.Append(a[pt]);
	for (; pm < matrix1.terms; pm++)
		matrix2.Append(matrix1.a[pm]);
}
