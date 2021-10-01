#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CIDR_IPv4 {
	uint8_t address[4];
	short subnet_bits;
	uint8_t network_address[4];
	uint8_t max_address[4];

	void Set_address();
	void Set_Network_Address();
	void Set_Max_Address();
public:
	void Check_Belonging(string input_ip);
	CIDR_IPv4(){
		Set_address();	
		Set_Network_Address();
		Set_Max_Address();
	}
};

class CIDR_IPv6 {
	uint16_t address[8];
	short prefix_length;
	uint16_t network_address[8];
public:
	void Set_adress();
	void Set_network_address();
	CIDR_IPv6() : address() {
		Set_adress();
		Set_network_address();
	}
};

int main()
{
	/*
	CIDR_IPv4 IPv4;
	string check_ip;
	while (true) {
		cout << "Enter IP address to check (IPv4): "; cin >> check_ip;
		IPv4.Check_Belonging(check_ip);
	}
	*/
	CIDR_IPv6 IPv6;
	return 1;
}

void CIDR_IPv4::Set_address()
{
	cout << "Enter new adress adress (address/subnet_bits): ";
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
			free_bits = 8 - subnet_bits % 10;
			subnet_bits = 0;
		}
		while (free_bits != 0) {
			max_address[i] += pow(2, free_bits - 1);
			free_bits--;
		}
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
		cout << "Yot IP belongs to the subnet" << endl;
	else
		cout << "Your IP does not belongs to the subnet" << endl;
}

void CIDR_IPv6::Set_adress() {
	cout << "Enter new adress adress (address/subnet_bits): ";
	string buff;
	for (int i = 0; i < 7; i++) {
		getline(cin, buff, ':');
		this->address[i] = stoul(buff, nullptr, 16);
	}
	getline(cin, buff, '/');
	this->address[7] = stoul(buff, nullptr, 16);
	cin >> prefix_length;
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
			if (prefix_length >= 8) {
				sixteenth = 16;
				prefix_length -= 16;
			}
			else {
				sixteenth = prefix_length % 10;
				prefix_length -= sixteenth;
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
