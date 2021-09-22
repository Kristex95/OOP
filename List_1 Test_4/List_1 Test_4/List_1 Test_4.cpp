#include <iostream>
using namespace std;

template <typename T>
class List {
	template <typename T>
	class Node {

	public:
		T data;
		Node* pNext;

		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T>* head;
public:
	List();
	~List();

	template <typename T>
	void push_back(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
		}
		else {
			Node<T>* current = this->head;
			while (current->pNext != nullptr) {
				current = current->pNext;
			}
			current->pNext = new Node<T>(data);

		}
		
		this->Size++;
	}
};

template <typename T>
List<T>::~List() {

}

template <typename T>
List<T>::List() {
	Size = 0;
	head = NULL;
}

int main() {
	List<int> list;
	for (int i = 0; i < 10; i++) {
		list.push_back(i);
	}
	
	return 1;
}