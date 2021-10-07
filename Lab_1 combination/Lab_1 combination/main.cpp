#include <iostream>
#include "CIDR_IPv4.h"
#include "CIDR_IPv6.h"
#include "Sparse_Matrix.h"


using namespace std;

int main() {
	CIDR_IPv4 ipv4("192.168.0.1/16");
	CIDR_IPv4 ipv4_local;
	Sparse_Matrix<CIDR_IPv4> s_matrix; //127.0.0.0 - localhost
	s_matrix.push_back(0, 0, ipv4);
	s_matrix.push_back(1, 1, ipv4_local);
	
	return 1;
}