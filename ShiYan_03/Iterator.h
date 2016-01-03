#include "Chain.cpp"//模板类
/**中文课本93页，复制并理解*/
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