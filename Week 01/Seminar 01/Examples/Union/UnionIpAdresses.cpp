#include <iostream>
using namespace std;
union IpAddress
{
	uint32_t address;
	unsigned char octets[4];
};

int main()
{
	IpAddress myAddress;
	myAddress.address = 16777343; // IN HEX: 0100007F
	// SO we are working in Little Endian and in the memory it looks like this:
	// 7F|00|00|01|
	std::cout << (int)myAddress.octets[0] << "."
		<< (int)myAddress.octets[1] << "."
		<< (int)myAddress.octets[2] << "."
		<< (int)myAddress.octets[3];

}