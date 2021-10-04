#include <string>
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

