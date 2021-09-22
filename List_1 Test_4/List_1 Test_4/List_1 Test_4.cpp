#include <iostream>
using namespace std;

template <typename T>
class List {

	template <typename T>
	class Node {

	public:
		T data;
		Node* pNext;

		//Node constructor
		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T>* head;
public:
	List();						//List constructor			
	~List();					//List destructor
	void push_back(T data);		//adds new element to the end of the list
	T& operator[](int index);	//gets the element by some index
	int find_by_data(T data);
};

template <typename T>
List<T>::~List() {

}

template <typename T>
List<T>::List() {								
	Size = 0;
	head = NULL;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)					//if the list is empty
	{					
		head = new Node<T>(data);
	}
	else									//if the list is not empty
	{									
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	this->Size++;
}

template <typename T>
T& List<T>::operator[](int index) {
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
int List<T>::find_by_data(T data)
{
	Node<T>* current = head;
	int counter = 0;
	while (current != nullptr) {
		if (current->data == data) {
			return counter;
		}
		current = current->pNext;
		counter++;
	}
	cout << "There is no data: " << data << endl;
	return 0;
}

int main() {
	List<int> list;
	for (int i = 0; i < 10; i++) {
		list.push_back(i+2);
	}
	cout << "Data index: " << list.find_by_data(5);
	return 1;
}