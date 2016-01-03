#include "stdafx.h"
#include "TridiagonalMatrix.h"

//ʵ��Store����������ӳ�䣨iΪ�У�jΪ�У���1��ʼ��
template <class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return *this;
	}
	switch (i - j)
	{
	case -1://�ϣ�min:1,2
		t[3 * j - 4] = x;//if min 4=6-2
		break;
	case 0://���Խ���
		t[3 * j - 3] = x;
		break;
	case 1://��,max:n,n-1
		t[3 * j - 2] = x;
		break;
	default:
		if (x != 0)
			throw MustBeZero();
	}
	return *this;
}

//ʵ��Retrieve����������ӳ��
template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return 0;
	}
	switch (i - j)//������Store��ȫһ����
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

//ʵ��Output����
template<class T>
void TridiagonalMatrix<T>::Output(ostream& out)const
{
	//����new T[n][n]�ı��벻����д��
	T** bint = new T*[n];
	for (int i = 0; i < n; i++) {
		bint[i] = new int[n];
	}
	//������ȡԪ�أ������ά����
	int k = 0; 
	for (int j = 0; j < n; j++){
		for (int i = 0; i < n; i++){
			if ((j - i) >= -1 && (j - i) <= 1)
				bint[i][j] = t[k++];
			else
				bint[i][j] = 0;
		}
	}
	//�����ά����
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			out << bint[i][j] << "\t";
		}
		out << endl;
	}
}

//����<<
template<class T>
ostream& operator<<(ostream &out, TridiagonalMatrix<T> &x)
{
	x.Output(out);
	return out;
}
