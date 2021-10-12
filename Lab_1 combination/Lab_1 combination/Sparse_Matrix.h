#include <iostream>
#include <stdexcept>
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
	int max_i;
	int max_j;
	Node<T>* head;
public:
	Sparse_Matrix(int max_i, int max_j);
	void add(int i, int j, T data);
	void find_by_data(T ip);
	T find_by_condition(std::string op, T ip);
	T find_by_indexes(int i, int j);
};

template <typename T>
Sparse_Matrix<T>::Sparse_Matrix(int max_i, int max_j) {
	if (max_i < 0 || max_j < 0) {
		throw invalid_argument("argument can't be less than 0");
	}
	this->max_i = max_i;
	this->max_j = max_j;
	head = nullptr;
}

template<typename T>
void Sparse_Matrix<T>::add(int i, int j, T data)
{
	if (i > max_i || j > max_j || i < 0 || j < 0) {
		throw invalid_argument("Wrong indexes");
	}
	if (data != T()) {
		if (head == nullptr)					//if the Sparse_List is empty
		{
			head = new Node<T>(i, j, data);
		}
		else									//if the Sparse_List is not empty
		{
			Node<T>* current = this->head;
			if (current->i == i && current->j == j) {
				current->data = data;
			}
			else {
				while (current->pNext != nullptr)
				{
					current = current->pNext;
				}
				current->pNext = new Node<T>(i, j, data);
			}
		}
	}
}

template<typename T>
T Sparse_Matrix<T>::find_by_indexes(int i, int j)
{
	if (i > max_i || j > max_j || i < 0 || j < 0) {
		throw invalid_argument("Wrong indexes");
	}
	Node<T>* current = this->head;
	while (current != nullptr) {
		if (i == current->i) {
			if (j == current->j) {
				return current->data;
			}
		}
		current = current->pNext;
	}
	return T();
}

template<typename T>
void Sparse_Matrix<T>::find_by_data(T _data)
{
	if (_data == T()) {
		cout << "Element can't be equal to (localhost)";
		return;
	}
	bool found = false;
	Node<T>* current = this->head;
	while (current != nullptr) {
		if (current->data == _data) {
			found = true;
			cout << "index is [" << current->i << "][" << current->j << "]" << endl;
		}
		current = current->pNext;
	}
	if (!found) {
		cout << "There is no element " << _data.To_string() << endl;
	}
}

template<typename T>
inline T Sparse_Matrix<T>::find_by_condition(std::string op, T cidr_ipv4)
{
	Node<T>* current = head;
	if (op == ">") {
		while (current != nullptr) {
			if (current->data > cidr_ipv4) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "<") {
		while (current != nullptr) {
			if (current->data < cidr_ipv4) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == ">=") {
		while (current != nullptr) {
			if (current->data >= cidr_ipv4) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "<=") {
		while (current != nullptr) {
			if (current->data <= cidr_ipv4) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	else if (op == "!=") {
		while (current != nullptr) {
			if (current->data != cidr_ipv4) {
				return current->data;
			}
			current = current->pNext;
		}
	}
	return T();
}