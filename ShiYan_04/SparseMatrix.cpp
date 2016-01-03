#include "stdafx.h"
#include "SparseMatrix.h"

//稀疏矩阵的构造函数
template <class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	if (maxTerms < 1){
		throw BadInitializers();
		return;
	}
	MaxTerms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = 0;//总元素数
	rows = cols = maxTerms;//行数=列数=最大元素数。就浪费一点资源吧。
}

//实现Append方法，添加一个元素
template<class T>
void SparseMatrix<T>::Append(const Term<T> & t)
{
	//把一个非零元素添加到*this中
	if (terms >= MaxTerms){
		throw NOMEM();
		return;
	}
	//重复，则更新值
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

//实现转置方法，互换每个元素的row,col
template<class T>
void SparseMatrix<T> ::MyTranspose() 
{
	for (int i = 0; i < terms; i++){
		int temp = a[i].col;
		a[i].col = a[i].row;
		a[i].row = temp;
	}
}

//实现相加方法，将新矩阵加到原来的矩阵
template<class T>
void SparseMatrix<T> ::MyAdd(SparseMatrix<T> &matrix){
	for (int j = 0; j < matrix.terms; j++){//逐个判断新矩阵中的元素
		bool need_add = true;
		for (int i = 0; i < terms; i++){//如果原矩阵中有，就相加
			if (a[i].row == matrix.a[j].row&&a[i].col == matrix.a[j].col){
				a[i].data += matrix.a[j].data;
				need_add = false;
			}
		}
		if (need_add){//没有，就添加
			a[terms] = matrix.a[j];
			terms++;
		}
	}
}

//实现Output方法
template<class T>
void SparseMatrix<T>::Output(ostream& out)const
{
	for (int i = 0; i < terms; i++)
		out << "a(" << a[i].row << "," << a[i].col << ")=" << a[i].data << endl;
}

//重载<<
template<class T>
ostream& operator<<(ostream &out, SparseMatrix<T> &x)
{
	x.Output(out);
	return out;
}

////////////////////////////////////////////课本上的方法，亲测可用

//实现转置方法
template<class T>
void SparseMatrix<T> ::Transpose(SparseMatrix<T> &matrix)const
{
	//把*this的转置结果传给matrix
	//matrix中是否有足够空间
	if (terms > matrix.MaxTerms)
		throw NOMEM();
	matrix.cols = rows;
	matrix.rows = cols;
	matrix.terms = terms;
	//ColSize[]:每列种的非零元素数   RowNext[]：转置后每行中非零元素在matrix中的下一个位置的下标
	int *ColSize, *RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[rows + 1];
	//初始化ColSize
	for (int i = 1; i < cols; i++)
	{
		ColSize[i] = 0;
	}
	//计算*this每行中非零元素个数
	for (int i = 0; i < terms; i++)
	{
		ColSize[a[i].col]++;
	}
	//给出matrix中每一行的起始点
	RowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
	{
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	}

	//执行转置操作
	for (int i = 0; i < terms; i++)
	{
		int j = RowNext[a[i].col]++;
		matrix.a[j].row = a[i].col;
		matrix.a[j].col = a[i].row;
		matrix.a[j].data = a[i].data;
	}
}

//实现Add方法 完成两个稀疏矩阵相加
template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &matrix1, SparseMatrix<T> &matrix2)const
{ //matrix2 = *this + matrix1
	if (rows != matrix1.rows || cols != matrix1.cols)
		throw SizeMismatch();
	matrix2.rows = rows;
	matrix2.cols = cols;
	matrix2.terms = 0;
	//定义*this和matrix1的游标
	int pt = 0;
	int pm = 0;
	//在*this和matrix1中遍历
	while (pt < terms&&pm < matrix1.terms)
	{
		//每一个元素的行主索引
		int indt = a[pt].row*cols + a[pt].col;
		int indm = matrix1.a[pm].row*cols + matrix1.a[pm].col;
		if (indt >indm)
		{//matrix1的元素在后
			matrix2.Append(a[pt]);
			pt++;
		}
		else
		{
			if (indt == indm)
			{//位置相同
				//仅当和不为零才添加到matrix2中
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
				//把matrix1中的下一个元素添加到matrix2中
				matrix2.Append(matrix1.a[pm]);
				pm++;
			}
		}
	}

	//复制剩余元素
	for (; pt < terms; pt++)
		matrix2.Append(a[pt]);
	for (; pm < matrix1.terms; pm++)
		matrix2.Append(matrix1.a[pm]);
}
