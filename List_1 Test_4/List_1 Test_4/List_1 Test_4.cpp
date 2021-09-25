#include <iostream>
using namespace std;

#pragma region Sparse_List
template <typename T>
class Sparse_List {

	template <typename T>
	class Node {

	public:
		T data;
		int index;
		Node* pNext;

		//Node constructor
		Node(T data = T(), int index = NULL, Node* pNext = nullptr) {
			this->data = data;
			this->index = index;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T>* head;
public:
	Sparse_List();				//Sparse_List constructor			
	~Sparse_List();				//Sparse_List destructor
	void push_back(T data);		//adds new element to the end of the Sparse_List
	T& operator[](int index);	//gets the element by some index
	int find_by_data(T data);
	T& find_by_condition(string op, int num);
};

template <typename T>
Sparse_List<T>::~Sparse_List() {

}

template <typename T>
Sparse_List<T>::Sparse_List() {								
	Size = 0;
	head = NULL;
}

template<typename T>
void Sparse_List<T>::push_back(T data)
{
	if (data != 0) {
		if (head == nullptr)					//if the Sparse_List is empty
		{					
			head = new Node<T>(data, Size);
		}
		else									//if the Sparse_List is not empty
		{									
			Node<T>* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = new Node<T>(data, Size);
		}
	}
	this->Size++;
}

template <typename T>
T& Sparse_List<T>::operator[](int index) {
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (current->index == index)				
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
int Sparse_List<T>::find_by_data(T data)
{
	Node<T>* current = head;
	while (current != nullptr) {
		if (current->data == data) {
			return current->index;
		}
		current = current->pNext;
	}
	cout << "There is no data: " << data << endl;
	return 0;
}

template<typename T>
T& Sparse_List<T>::find_by_condition(string op, int num)
{
	Node<T>* current = head;
	if (op == ">") {
		while (current != nullptr) {
			if (current->data > num) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "<") {
		while (current != nullptr) {
			if (current->data < num) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == ">=") {
		while (current != nullptr) {
			if (current->data >= num) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "<=") {
		while (current != nullptr) {
			if (current->data <= num) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "!=") {
		while (current != nullptr) {
			if (current->data != num) {
				return current->data;
			}
			current = current->pNext;
		}
	}
}
#pragma endregion

int main() {
	Sparse_List<int> sparse_List;
	int op;
	do{
		system("cls");
		cout << "1. push_back()\n";
		cin >> op;
		switch (op)
		{
		case 1:
			int i;
			system("cls");
			cout << "Enter number to add: "; cin >> i;
			sparse_List.push_back(i);
			break;
		default:
			break;
		}
	} while (op != 0);
	return 1;
}

