#include <iostream>

using namespace std;
#pragma once
template <typename T>
class Sparse_Matrix {
	template <typename T>
	class Node {

	public:
		int i;
		int j;
		T data;
		Node* pNext;

		Node(int i = NULL, int j = NULL, T data = T(), Node* pNext = nullptr) {
			this->i = i;
			this->j = j;
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node<T>* head;
public:
	Sparse_Matrix();
	void push_back(int i, int j, T data);
	int find_by_indexes(int i, int j);
	void find_by_data(T _data);
	int find_by_condition(std::string op, int num);
};

template <typename T>
Sparse_Matrix<T>::Sparse_Matrix() {
	head = nullptr;
}

template<typename T>
void Sparse_Matrix<T>::push_back(int i, int j, T data)
{
	if (data != T()) {
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
