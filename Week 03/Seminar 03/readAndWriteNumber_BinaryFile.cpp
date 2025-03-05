#include <iostream>
#include <fstream>

namespace Constants {
	constexpr char FILE_NAME[] = "number.dat";
}

using namespace Constants;

int main() {
	// writing a number to binary file
	{
		int n = 321;
		std::ofstream ofs(FILE_NAME, std::ios::binary);
		if (!ofs.is_open()) {
			return -1;
		}
		ofs.write((const char*)&n, sizeof(n)); // since write expects an address we convert it to a pointer using &n
											   // and then we cast it to const char*
		ofs.close();
	}

	// reading a number from binary file
	{
		int n;
		std::ifstream ifs(FILE_NAME, std::ios::binary);
		if (!ifs.is_open()) {
			return -1;
		}
		ifs.read((char*)&n, sizeof(n)); // read expects an address, so we convert n to a pointer using &n
										// and we cast it to char*
		std::cout << n << std::endl;
		ifs.close();
	}
}