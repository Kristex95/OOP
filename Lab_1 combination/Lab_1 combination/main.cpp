#include <iostream>
#include "CIDR_IPv4.h"
#include "CIDR_IPv6.h"
#include "Sparse_Matrix.h"
#include "Sparse_List.h"

using namespace std;

int main() {
	CIDR_IPv6 ipv6_0("9084:acb:0001:1111:0000:bf14:24ff:ffff/16");
	CIDR_IPv6 ipv6("3584:acb:0101:1111:0000:bf14:24cf:aaff/16");
	CIDR_IPv4 ipv4_local;
	
	Sparse_Matrix<CIDR_IPv6> s_matrix(5, 5); //127.0.0.0/8 & 0:0:0:0:0:0:0:1 - localhost
	s_matrix.push_back(1, 1, ipv6);
	s_matrix.find_by_data(ipv6_0);
	CIDR_IPv6 New = s_matrix.find_by_indexes(1, 1);
	cout << New.To_string();
	/*
	Sparse_List<CIDR_IPv6> s_list;
	s_list.push_back(ipv6);
	s_list.push_back(CIDR_IPv6());
	s_list.push_back(ipv6_0);
	s_list.push_back(ipv6);
	s_list.push_back(CIDR_IPv6());
	CIDR_IPv6 A = s_list[4];
	cout << ipv6.To_string();
	*/
	return 1;
}