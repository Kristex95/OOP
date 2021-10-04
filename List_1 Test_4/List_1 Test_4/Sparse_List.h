#include <string>
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
	Sparse_List();				//Sparse_List constructor						//Sparse_List destructor
	void push_back(T data);		//adds new element to the end of the Sparse_List
	T& operator[](int index);	//gets the element by some index
	int find_by_data(T data);
	T& find_by_condition(std::string op, int num);
};

