#include "CIDR_IPv4.h"
#include <iostream>
#include <sstream>

CIDR_IPv4::CIDR_IPv4() {
	for (auto i : address) {
		address[i] = 0;
	}
	subnet_bits = 0;
	for (auto i : network_address) {
		network_address[i] = 0;
	}
	for (auto i : max_address) {
		max_address[i] = 0;
	}
}

CIDR_IPv4::CIDR_IPv4(string ip) {
	Set_address(ip);
	Set_Network_Address();
	Set_Max_Address();
}

void CIDR_IPv4::Set_address(string buff)
{
	stringstream sstream(buff);
	for (int i = 0; i < 3; i++) {
		getline(sstream, buff, '.');
		int byte = stoi(buff);
		if (byte >= 256) {
			byte = 255;
		}
		else if (byte < 0) {
			byte = 0;
		}
		address[i] = byte;
	}
	getline(sstream, buff, '/');
	int byte = stoi(buff);
	if (byte >= 256) {
		throw exception("value greater than 255");
	}
	else if (byte < 0) {
		throw exception("value less than 0");
	}
	address[3] = byte;

	getline(sstream, buff);
	subnet_bits = stoi(buff);
	if (subnet_bits < 0) {
		subnet_bits = 0;
	}
	else if (subnet_bits > 32) {
		subnet_bits = 32;
	}
}

void CIDR_IPv4::Set_Network_Address()
{
	uint8_t address[4];
	for (int i = 0; i < 4; i++) {
		address[i] = this->address[i];
	}

	uint8_t mask_bits[4] = { 0 };
	int subnet_bits = this->subnet_bits;

	for (int i = 0; i < 4; i++) {
		int octet = 0;
		if (subnet_bits != 0) {
			if (subnet_bits >= 8) {
				octet = 8;
				subnet_bits -= 8;
			}
			else {
				octet = subnet_bits % 10;
				subnet_bits -= octet;
			}
			int degree = 7;
			while (octet != 0) {
				mask_bits[i] += pow(2, degree);
				degree--;
				octet--;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		this->network_address[i] = this->address[i] & mask_bits[i];
	}
}

void CIDR_IPv4::Set_Max_Address() {
	int subnet_bits = this->subnet_bits;
	for (int i = 0; i < 4; i++) {
		max_address[i] = network_address[i];
		int free_bits = 8;
		if (subnet_bits >= 8) {
			subnet_bits -= 8;
			free_bits = 0;
		}
		else if (subnet_bits < 8 && subnet_bits > 0) {
			free_bits = 8 - subnet_bits;
			subnet_bits = 0;
		}
		while (free_bits != 0) {
			max_address[i] += pow(2, free_bits - 1);
			free_bits--;
		}
	}
}

int CIDR_IPv4::Check_Belonging(string input_ip)
{
	char delim = '.';
	uint8_t user_ip[4];
	stringstream sstream(input_ip);
	string buff;
	for (int i = 0; i < 3; i++) {
		getline(sstream, buff, delim);
		user_ip[i] = stoi(buff);
	}
	getline(sstream, buff);
	user_ip[3] = stoi(buff);

	bool belongs = true;
	for (int i = 0; i < 4; i++) {
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
