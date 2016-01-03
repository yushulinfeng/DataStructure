#include "stdafx.h"

/*�����Ǿ�����*/
template<class T>
class LowerMatrix
{
public:
	LowerMatrix(int size = 5){
		n = size;
		t = new T[n*(n + 1) / 2];
	}
	~LowerMatrix(){
		delete[]t;
	}
	LowerMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const;
	void Output(ostream& out)const;
private:
	int n;//����ά��
	T *t;//��������һά����
};