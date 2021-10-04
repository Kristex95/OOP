#include "CIDR_IPv6.h" 
#include <iostream>
#include <sstream>

CIDR_IPv6::CIDR_IPv6() {
	for (auto i : address) {
		address[i] = 0;
	}
	prefix_length = 0;
	for (auto i : network_address) {
		network_address[i] = 0;
	}
	for (auto i : max_address) {
		max_address[i] = 0;
	}
}

CIDR_IPv6::CIDR_IPv6(string ip) {
	Set_address(ip);
	Set_network_address();
	Set_Max_Address();
}

void CIDR_IPv6::Set_address(string buff) {
	stringstream sstream(buff);
	for (int i = 0; i < 7; i++) {
		getline(sstream, buff, ':');
		this->address[i] = stoul(buff, nullptr, 16);
	}
	getline(sstream, buff, '/');
	this->address[7] = stoul(buff, nullptr, 16);
	getline(sstream, buff, '/');
	this->prefix_length = stoi(buff);
}

void CIDR_IPv6::Set_network_address()
{
	uint16_t address[8];
	for (int i = 0; i < 8; i++) {
		address[i] = this->address[i];
	}

	uint16_t mask_bits[8] = { 0 };
	int prefix_length = this->prefix_length;

	for (int i = 0; i < 8; i++) {
		int sixteenth = 0;
		if (prefix_length != 0) {
			if (prefix_length >= 16) {
				sixteenth = 16;
				prefix_length -= 16;
			}
			else {
				sixteenth = prefix_length;
				prefix_length = 0;
			}
			int degree = 15;
			while (sixteenth != 0) {
				mask_bits[i] += pow(2, degree);
				degree--;
				sixteenth--;
			}
		}
	}
	//9084:acb:0001:1111:0000:bf14:24ff:ffff
	for (int i = 0; i < 8; i++) {
		this->network_address[i] = this->address[i] & mask_bits[i];
	}

}

void CIDR_IPv6::Set_Max_Address()
{
	int prefix_length = this->prefix_length;
	for (int i = 0; i < 8; i++) {
		max_address[i] = network_address[i];
		int free_bits = 16;
		if (prefix_length >= 16) {
			prefix_length -= 16;
			free_bits = 0;
		}
		else if (prefix_length < 16 && prefix_length > 0) {
			free_bits = 16 - prefix_length;
			prefix_length = 0;
		}
		while (free_bits != 0) {
			max_address[i] += pow(2, free_bits - 1);
			free_bits--;
		}
	}
}

int CIDR_IPv6::Check_Belonging(string input_ip)
{
	char delim = ':';
	uint16_t user_ip[8];
	stringstream sstream(input_ip);
	string buff;
	for (int i = 0; i < 7; i++) {
		getline(sstream, buff, delim);
		user_ip[i] = stoul(buff, nullptr, 16);
	}
	getline(sstream, buff);
	user_ip[7] = stoul(buff, nullptr, 16);

	bool belongs = true;
	for (int i = 0; i < 8; i++) {
		if (user_ip[i] >= network_address[i] && user_ip[i] <= max_address[i]) {

		}
		else {
			belongs = false;
			break;
		}
	}
	if (belongs)
		return 1;
	else
		return 0;
}
