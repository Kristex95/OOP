#pragma once
#include <cstdint>
#include <string>
using namespace std;

class CIDR_IPv6 {
private:
	uint16_t address[8];
	short prefix_length;
	uint16_t network_address[8];
	uint16_t max_address[8];
	void Set_address(string ip);
	void Set_network_address();
	void Set_Max_Address();
public:
	string To_string();
	bool Check_Belonging(string input_ip);
	CIDR_IPv6();
	CIDR_IPv6(string ip);
};

