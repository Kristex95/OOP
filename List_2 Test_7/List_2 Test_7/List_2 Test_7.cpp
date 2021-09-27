#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CIDR_IPv4 {
	uint8_t IP[4];
	uint8_t mask;
public:
	void Set_IP();
	CIDR_IPv4() : IP() {
		Set_IP();
	}
};

class IPv6 {
	uint16_t IP[8];

public:
	void Set_IP();
	IPv6() : IP() {
		Set_IP();
	}
};

int main()
{
	//IPv6 ipv6;
	CIDR_IPv4 ipv4;
	return 1;
}

void IPv6::Set_IP() {
	cout << "Enter new IP adress: ";
	string buff;
	for (int i = 0; i < 7; i++) {
		getline(cin, buff, ':');
		IP[i] = stoul(buff, nullptr, 16);
	}
	getline(cin, buff);
	IP[7] = stoul(buff, nullptr, 16);
}

void CIDR_IPv4::Set_IP()
{
	cout << "Enter new IP adress: ";
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
		IP[i] = byte;
	}
	getline(cin, buff);
	int byte = stoi(buff);
	if (byte >= 256) {
		byte = 255;
	}
	else if (byte < 0) {
		byte = 0;
	}
	IP[3] = byte;
}
