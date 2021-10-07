#include "CIDR_IPv4.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

CIDR_IPv4::CIDR_IPv4() {
	address[0] = 127;
	for (int i = 1; i < 4; i++) {
		address[i] = 0;
	}
	subnet_bits = 8;
	Set_Network_Address();
	Set_Max_Address();
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
			throw invalid_argument("Value greater than 255");
		}
		else if (byte < 0) {
			throw invalid_argument("Value less than 0");
		}
		address[i] = byte;
	}
	getline(sstream, buff, '/');
	int byte = stoi(buff);
	if (byte >= 256) {
		throw invalid_argument("Value greater than 255");
	}
	else if (byte < 0) {
		throw invalid_argument("Value less than 0");
	}
	address[3] = byte;

	getline(sstream, buff);
	subnet_bits = stoi(buff);
	if (subnet_bits < 0) {
		throw invalid_argument("Subnet bits value is less than 0");
	}
	else if (subnet_bits > 32) {
		throw invalid_argument("Subnet bits value is greater than 32");
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

bool CIDR_IPv4::Check_Belonging(string input_ip)
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
	return belongs;

}

string CIDR_IPv4::To_string() {
	string res;
	for (int i = 0; i < 3; i++) {
		res += to_string(address[i]) + '.';
	}
	res += to_string(address[3]) + '/' + to_string(subnet_bits);
	return res;
}

bool operator!=(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = false;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] != b.address[i]) {
			res = true;
			break;
		}
	}
	if (a.subnet_bits != b.subnet_bits) {
		res = true;
	}
	return res;
}

bool operator>(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = false;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] > b.address[i]) {
			res = true;
			break;
		}
		else if (a.address[i] == b.address[i]) {

		}
		else {
			break;
		}
	}
	return res;
}

bool operator<(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = false;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] < b.address[i]) {
			res = true;
			break;
		}
		else if (a.address[i] == b.address[i]) {

		}
		else {
			break;
		}
	}
	return res;
}

bool operator>=(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = false;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] > b.address[i]) {
			res = true;
		}
		else if (a.address[i] == b.address[i]) {

		}
		else {
			res = false;
			break;
		}
	}
	return res;
}

bool operator<=(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = false;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] < b.address[i]) {
			res = true;
		}
		else if (a.address[i] == b.address[i]) {

		}
		else {
			res = false;
			break;
		}
	}
	return res;
}

bool operator==(const CIDR_IPv4& a, const CIDR_IPv4& b)
{
	bool res = true;
	for (int i = 0; i < 4; i++) {
		if (a.address[i] != b.address[i]) {
			res = false;
			break;
		}
	}
	if (a.subnet_bits != b.subnet_bits) {
		res = false;
	}
	return res;
}
