#include <iostream>
#include <stdexcept>
using namespace std;

#pragma once
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
	void push_back(T data);		//adds new element to the end of the Sparse_List
	T operator[](int index);	//gets the element by some index
	T find_by_data(T data);
	T& find_by_condition(std::string op, int num);
};

template <typename T>
Sparse_List<T>::Sparse_List() {
	Size = 0;
	head = NULL;
}

template<typename T>
void Sparse_List<T>::push_back(T data)
{
	if (data != T()) {
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


template<typename T>
T Sparse_List<T>::operator[](int index) {
	if (index > Size && index < 0) {
		throw invalid_argument("Invalid index value");
	}
	Node<T>* current = this->head;
	while (current != nullptr) {
		if (current->index == index) {
			return current->data;
		}
		else if (index < current->index) {
			return T();
		}
		else if (index > current->index) {
			current = current->pNext;
		}
	}
	return T();
}

template<typename T>
T Sparse_List<T>::find_by_data(T data)
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
