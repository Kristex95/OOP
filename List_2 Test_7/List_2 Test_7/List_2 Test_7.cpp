#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "CIDR_IPv4.h"
#include "CIDR_IPv6.h"

using namespace std;

int main() {
	CIDR_IPv4 ipv4("192.168.0.1/12");
	if (ipv4.Check_Belonging("192.167.88.88")) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	CIDR_IPv6 ipv6("9084:acb:0001:1111:0000:bf14:24ff:ffff/64");
	if (ipv6.Check_Belonging("9084:acb:0001:1112:0000:bf14:24ff:ffff")) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 1;
}
