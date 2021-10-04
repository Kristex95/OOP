#include "Sparse_List.h"
#include <string>
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
T& Sparse_List<T>::find_by_condition(std::string op, int num)
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