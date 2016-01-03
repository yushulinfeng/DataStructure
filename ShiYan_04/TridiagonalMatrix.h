#include "stdafx.h"

/*三对角矩阵类*/
template<class T>
class TridiagonalMatrix
{
public:
	TridiagonalMatrix(int size = 5){
		n = size;
		t = new T[3 * n - 2];
	}
	~TridiagonalMatrix(){
		delete[]t;
	}
	TridiagonalMatrix<T>& Store(const T& x, int i, int j);//存入
	T Retrieve(int i, int j)const;//取出
	void Output(ostream& out)const;//输出
private:
	int n;//矩阵维数
	T *t;//数组指针
};