#include "stdafx.h"
#include "TridiagonalMatrix.h"

//实现Store方法，按列映射（i为行，j为列，从1开始）
template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return *this;
	}
	switch (i - j)
	{
	case -1://上，min:1,2
		t[3 * j - 4] = x;//if min 4=6-2
		break;
	case 0://主对角线
		t[3 * j - 3] = x;
		break;
	case 1://下,max:n,n-1
		t[3 * j - 2] = x;
		break;
	default:
		if (x != 0)
			throw MustBeZero();
	}
	return *this;
}

//实现Retrieve方法，按列映射
template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return 0;
	}
	switch (i - j)//跟上面Store完全一样。
	{
	case -1:
		return t[3 * j - 4];
	case 0:
		return t[3 * j - 3];
	case 1:
		return t[3 * j - 2];
	default:
		return 0;
	}
}

//实现Output方法
template<class T>
void TridiagonalMatrix<T>::Output(ostream& out)const
{
	//就是new T[n][n]的编译不报错写法
	T** bint = new T*[n];
	for (int i = 0; i < n; i++) {
		bint[i] = new int[n];
	}
	//按列提取元素，存入二维数组
	int k = 0; 
	for (int j = 0; j < n; j++){
		for (int i = 0; i < n; i++){
			if ((j - i) >= -1 && (j - i) <= 1)
				bint[i][j] = t[k++];
			else
				bint[i][j] = 0;
		}
	}
	//输出二维数组
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			out << bint[i][j] << "\t";
		}
		out << endl;
	}
}

//重载<<
template<class T>
ostream& operator<<(ostream &out, TridiagonalMatrix<T> &x)
{
	x.Output(out);
	return out;
}
