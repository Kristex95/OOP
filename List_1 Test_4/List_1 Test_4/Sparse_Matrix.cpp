#include "Sparse_Matrix.h"
#include <string>
template <typename T>
Sparse_Matrix<T>::Sparse_Matrix() {
	head = nullptr;
}

template<typename T>
void Sparse_Matrix<T>::push_back(int i, int j, T data)
{
	if (data != 0) {
		if (head == nullptr)					//if the Sparse_List is empty
		{
			head = new Node<T>(i, j, data);
		}
		else									//if the Sparse_List is not empty
		{
			Node<T>* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = new Node<T>(i, j, data);
		}
	}
}

template<>
int Sparse_Matrix<int>::find_by_indexes(int i, int j)
{
	Node<int>* current = this->head;
	while (current != nullptr) {
		if (i == current->i) {
			if (j == current->j) {
				return current->data;
			}
		}
		current = current->pNext;
	}
	return 0;
}

template<typename T>
void Sparse_Matrix<T>::find_by_data(T _data)
{
	if (_data == 0) {
		cout << "Element can't be equal to 0";
		return;
	}
	bool found = false;
	Node<int>* current = this->head;
	while (current != nullptr) {
		if (current->data == _data) {
			found = true;
			cout << "index is [" << current->i << "][" << current->j << "]" << endl;
		}
		current = current->pNext;
	}
	if (!found) {
		cout << "There is no element " << _data << endl;
	}
	return;
}

template<>
int Sparse_Matrix<int>::find_by_condition(std::string op, int num)
{
	Node<int>* current = head;
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
	return 0;
}