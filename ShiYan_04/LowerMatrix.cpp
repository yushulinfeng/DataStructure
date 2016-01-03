#include "stdafx.h"
#include "LowerMatrix.h"

//ʵ��Store����������ӳ�䣨iΪ�У�jΪ�У���1��ʼ��
template<class T>
LowerMatrix<T>& LowerMatrix<T>::Store(const T& x, int i, int j)
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return *this;
	}
	if (i - j >= 0)//s(n)-s(n-j+1) + (n-j+1)-(n-i) -1; 
		t[(n*(n + 1) / 2) - ((n - j + 1)*(n - j + 2) / 2) + (n - j + 1) - (n - i) - 1] = x;
	else if (x != 0)
		throw MustBeZero();
	return *this;
}

//ʵ��Retrieve����������ӳ��
template <class T>
T LowerMatrix<T>::Retrieve(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n){
		throw OutOfBounds();
		return 0;
	}
	if (i - j >= 0)//ͬ��
		return t[(n*(n + 1) / 2) - ((n - j + 1)*(n - j + 2) / 2) + (n - j + 1) - (n - i) - 1];
	else
		return 0;
}

//ʵ��Output����
template<class T>
void LowerMatrix<T>::Output(ostream& out)const
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
			if (i - j >= 0){
				bint[i][j] = t[k];
				k++;
			}else
				bint[i][j] = 0;
		}
	}
	//�����ά����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++){
			out << bint[i][j] << "\t";
		}
		out << endl;
	}
}

//����<<
template<class T>
ostream& operator<<(ostream & out, LowerMatrix<T> & x)
{
	x.Output(out);
	return out;
}
