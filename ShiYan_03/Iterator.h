#include "Chain.cpp"//ģ����
/**���Ŀα�93ҳ�����Ʋ����*/
template<class T>
class ListIterator {
public:
	T* Initialize(const Chain<T>& c){
		location = c.firstnode;
		if (location)
			return &location->data;
		return 0;
	}
	T* Next(){
		if (!location)
			return 0;
		location = location->next;
		if (location)
			return &location->data;
		return 0;
	}
private:
	Node<T> *location;
};