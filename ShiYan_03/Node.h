
template <class T>
class Node{
public :
	//���ݺͽڵ�ָ��
	T data;
	Node<T> *next;
	//������
	Node(const T& data, Node<T>* next){
		this->data = data;
		this->next = next;
	}
};