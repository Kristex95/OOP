#include <iostream>
#include "CIDR_IPv4.h"
#include "CIDR_IPv6.h"
#include "Sparse_Matrix.h"


using namespace std;

int main() {
	CIDR_IPv4 ipv4_0("100.168.0.1/16");
	CIDR_IPv4 ipv4("192.168.0.1/16");
	CIDR_IPv4 ipv4_local;
	Sparse_Matrix<CIDR_IPv4> s_matrix(5, 5); //127.0.0.0 - localhost

	s_matrix.push_back(1, 1, ipv4);
	s_matrix.find_by_data(ipv4_0);

	CIDR_IPv4 NEw = s_matrix.find_by_indexes(1, 1);
	cout << NEw.To_string();
	return 1;
}