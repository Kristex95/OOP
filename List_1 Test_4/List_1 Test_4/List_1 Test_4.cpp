#include <iostream>
#include <typeinfo>
#include "Sparse_List.h"
#include "Sparse_Matrix.h"
using namespace std;

#pragma region Sparse_Matrix

	


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

