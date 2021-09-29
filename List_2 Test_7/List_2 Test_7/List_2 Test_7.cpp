#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CIDR_IPv4 {
	uint8_t address[4];
	short subnet_bits;
	uint8_t network_address[4];

	void Set_address();
	void Set_Network_Address();
public:
	void Check_Belonging(string input_ip);
	CIDR_IPv4(){
		Set_address();	
		Set_Network_Address();
	}
};

class CIDR_IPv6 {
	uint16_t adress[8];

public:
	void Set_adress();
	CIDR_IPv6() : adress() {
		Set_adress();
	}
};

int main()
{
	//CIDR_IPv6 IPv6;
	CIDR_IPv4 IPv4;
	IPv4.Check_Belonging("192.0.1.1");
	return 1;
}

void CIDR_IPv4::Set_address()
{
	cout << "Enter new adress adress (adress/subnet_bits): ";
	string buff;
	for (int i = 0; i < 3; i++) {
		getline(cin, buff, '.');
		int byte = stoi(buff);
		if (byte >= 256) {
			byte = 255;
		}
		else if (byte < 0) {
			byte = 0;
		}
		address[i] = byte;
	}
	getline(cin, buff, '/');
	int byte = stoi(buff);
	if (byte >= 256) {
		byte = 255;
	}
	else if (byte < 0) {
		byte = 0;
	}
	address[3] = byte;

	cin >> subnet_bits;
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

	uint8_t mask_bits[4] = {0};
	int subnet_bits = this->subnet_bits;

	for (int i = 0; i < 4; i++) {
		int octet = 0;
		if (subnet_bits >= 8) {
			octet = 8;
			subnet_bits -= 8;
		}
		else {
			octet = subnet_bits % 10;
		}
		int degree = 7;
		while (octet != 0){
			mask_bits[i] += pow(2, degree);
			degree--;
			octet--;
		}
	}

	for (int i = 0; i < 4; i++) {
		this->network_address[i] = this->address[i] & mask_bits[i];
	}
}

void CIDR_IPv4::Check_Belonging(string input_ip)
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


}

void CIDR_IPv6::Set_adress() {
	cout << "Enter new adress adress (adress/subnet_bits): ";
	string buff;
	for (int i = 0; i < 7; i++) {
		getline(cin, buff, ':');
		adress[i] = stoul(buff, nullptr, 16);
	}
	getline(cin, buff, '/');
	adress[7] = stoul(buff, nullptr, 16);
}