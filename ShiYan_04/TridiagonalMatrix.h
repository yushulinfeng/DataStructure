#include "stdafx.h"

/*���ԽǾ�����*/
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
	TridiagonalMatrix<T>& Store(const T& x, int i, int j);//����
	T Retrieve(int i, int j)const;//ȡ��
	void Output(ostream& out)const;//���
private:
	int n;//����ά��
	T *t;//����ָ��
};