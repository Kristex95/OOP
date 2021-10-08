#include "CIDR_IPv6.h" 
#include <iostream>
#include <sstream>
//ip example 
//9084:acb:0001:1111:0000:bf14:24ff:ffff

CIDR_IPv6::CIDR_IPv6() {
	for (int i = 0; i < 7; i++) {
		address[i] = 0;
	}
	address[7] = 1;
	prefix_length = 128;
	Count_network_address();
	Count_Max_Address();
}

CIDR_IPv6::CIDR_IPv6(string ip) {
	Set_address(ip);
	Count_network_address();
	Count_Max_Address();
}

void CIDR_IPv6::Set_address(string buff) {
	stringstream sstream(buff);
	for (int i = 0; i < 7; i++) {
		getline(sstream, buff, ':');
		if(buff.length() > 4){
			throw invalid_argument("Invalid argumet in ip address");
		}
		this->address[i] = stoul(buff, nullptr, 16);
	}
	getline(sstream, buff, '/');
	if (buff.length() > 4) {
		throw invalid_argument("Invalid argumet in ip address");
	}
	this->address[7] = stoul(buff, nullptr, 16);
	getline(sstream, buff);
	this->prefix_length = stoi(buff);
}

void CIDR_IPv6::Count_network_address()
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
	for (int i = 0; i < 8; i++) {
		this->network_address[i] = this->address[i] & mask_bits[i];
	}

}

void CIDR_IPv6::Count_Max_Address()
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

bool CIDR_IPv6::Check_Belonging(string input_ip)
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
	return belongs;
}

string CIDR_IPv6::To_string() {
	string res;
	string num = "0123456789abcdef";
	uint16_t address[8];
	for (int i = 0; i < 8; i++) {
		address[i] = this->address[i];
	}
	
	for (int i = 0; i < 7; i++) {
		int t = pow(16, 3);
		for (int j = 0; j < 4; j++) {
			res += num[address[i] / t];
			address[i] = address[i] % t;
			t /= 16;
		}
		res += address[i] + ':';
	}
	int t = pow(16, 3);
	for (int j = 0; j < 4; j++) {
		res += num[address[7] / t];
		address[7] = address[7] % t;
		t /= 16;
	}
	res += address[7] + "/" + to_string(prefix_length);
	return res;
}

bool operator!=(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = false;
	for (int i = 0; i < 8; i++) {
		if (a.address[i] != b.address[i]) {
			res = true;
			break;
		}
	}
	if (a.prefix_length != b.prefix_length) {
		res = true;
	}
	return res;
}

bool operator>(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = false;
	for (int i = 0; i < 8; i++) {
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

bool operator<(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = false;
	for (int i = 0; i < 8; i++) {
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

bool operator>=(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = false;
	for (int i = 0; i < 8; i++) {
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

bool operator<=(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = false;
	for (int i = 0; i < 8; i++) {
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

bool operator==(const CIDR_IPv6& a, const CIDR_IPv6& b)
{
	bool res = true;
	for (int i = 0; i < 8; i++) {
		if (a.address[i] != b.address[i]) {
			res = false;
			break;
		}
	}
	if (a.prefix_length != b.prefix_length) {
		res = false;
	}
	return res;
}
