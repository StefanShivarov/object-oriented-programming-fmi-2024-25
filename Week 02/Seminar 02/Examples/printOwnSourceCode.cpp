#include <iostream>
#include <fstream>

using std::endl;

int main() {
	std::ifstream ifs("printOwnSourceCode.cpp");
	char buff[1024];

	while (!ifs.eof()) {
		ifs.getline(buff, 1024);
		std::cout << buff << endl;;
	}

	ifs.close();
}
