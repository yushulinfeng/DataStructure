
template <class T>
class Node{
public :
	//数据和节点指针
	T data;
	Node<T> *next;
	//构造器
	Node(const T& data, Node<T>* next){
		this->data = data;
		this->next = next;
	}
};