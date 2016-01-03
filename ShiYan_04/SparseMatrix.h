#include "stdafx.h"

/* 稀疏矩阵-行主映射*/

//矩阵元素 定义
template <class T>
class Term
{
public:
	int row, col;
	T data;
};

//稀疏矩阵 类定义
template <class T>
class SparseMatrix
{
public:
	SparseMatrix(int MaxTerms = 5);
	~SparseMatrix(){ delete[]a; }
	void MyTranspose();//转置(自身改变)
	void MyAdd(SparseMatrix<T> &matrix);//相加(自身改变)
	void Append(const Term<T> &t);//添加元素
	void Output(ostream& out)const;
	//书上的两个方法，测试均可行
	void Transpose(SparseMatrix<T> &matrix)const;//转置(result=matrix)
	void Add(const SparseMatrix<T> &matrix1, SparseMatrix<T> &matrix2)const;//相加(result=matrix2)
private:
	int rows, cols;//矩阵维数
	int terms;//矩阵非0元素个数
	Term<T> *a;//储存非零元素的数组
	int MaxTerms;//数组a的大小
};
