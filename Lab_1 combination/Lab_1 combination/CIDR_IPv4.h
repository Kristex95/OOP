#pragma once
#include <cstdint>
#include <string>
using namespace std;

class CIDR_IPv4 {
private:
	uint8_t address[4]; 
	short subnet_bits;
	uint8_t network_address[4];
	uint8_t max_address[4];

	void Set_address(string ip);
	void Count_Network_Address();
	void Count_Max_Address();
public:
	string To_string();
	bool Check_Belonging(string input_ip);
	CIDR_IPv4();
	CIDR_IPv4(string ip);
	friend bool operator!= (const CIDR_IPv4& a, const CIDR_IPv4& b);
	friend bool operator> (const CIDR_IPv4& a, const CIDR_IPv4& b);
	friend bool operator< (const CIDR_IPv4& a, const CIDR_IPv4& b);
	friend bool operator>= (const CIDR_IPv4& a, const CIDR_IPv4& b);
	friend bool operator<= (const CIDR_IPv4& a, const CIDR_IPv4& b);
	friend bool operator== (const CIDR_IPv4& a, const CIDR_IPv4& b);
};

