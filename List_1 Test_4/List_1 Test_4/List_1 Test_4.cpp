﻿#include <iostream>
#include <typeinfo>
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

#pragma region Sparse_Matrix
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
	int find_by_condition(string op, int num);
};
	
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
	if(_data == 0){
		cout << "Element can't be equal to 0";
		return;
	}
	bool found = false;
	Node<int>* current = this->head;
	while (current != nullptr) {
		if (current->data == _data){
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
int Sparse_Matrix<int>::find_by_condition(string op, int num)
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

#pragma endregion

int main() {
	int i, j, data, compareVal;
	string operation;
	Sparse_List<int> sparse_List;
	Sparse_Matrix<int> sparse_matrix;
	int op;
	do{
		cout << "Sparse_List\t Sparse_Matrix\n----1------push_back-------5----\n----2-----find_by_index----6----\n----3-----find_by_data-----7----\n----4---find_by_condition--8----";
		cin >> op;
		system("cls");
		switch (op)
		{
		case 1:
			
			cout << "Enter number to add: "; cin >> i;
			sparse_List.push_back(i);
			break;
		case 2:
			cout << "Enter index: "; cin >> i;
			cout << "Your element: " << sparse_List[i];
			break;
		case 3:
			cout << "Enter value: "; cin >> data;
			cout << "The index is: " << sparse_List.find_by_data(data);
			break;
		case 4:
			cout << "Enter operation (<, > , <=, >=, !=): "; cin >> operation;
			cout << "Enter value to compare: "; cin >> compareVal;
			data = sparse_List.find_by_condition(operation, compareVal);
			if (data != 0) {
				cout << "\nThe first element to find under your condition: " << data << endl;
			}
			else if (data == 0) {
				cout << "No elements for your condition" << endl;
			}
			break;
		case 5:
			cout << "Enter i: "; cin >> i;
			cout << "Enter j: "; cin >> j;
			cout << "Enter number: "; cin >> data;
			sparse_matrix.push_back(i, j, data);
			break;
		case 6:
			cout << "Enter i: "; cin >> i;
			cout << "Enter j: "; cin >> j;
			cout << "Yout element: " << sparse_matrix.find_by_indexes(i, j) << endl;
			break;
		case 7:
			cout << "Enter elemnt: "; cin >> data;
			sparse_matrix.find_by_data(data);
			break;
		case 8:
			cout << "Enter operation (<, > , <=, >=, !=): "; cin >> operation;
			cout << "Enter value to compare: "; cin >> compareVal;
			data = sparse_matrix.find_by_condition(operation, compareVal);
			if (data != 0){
				cout << "\nThe first element to find under your condition: " << data << endl;
			}
			else if (data == 0) {
				cout << "No elements for your condition" << endl;
			}
			break;
		default:
			break;
		}
	} while (op != 0);
	return 1;
}

