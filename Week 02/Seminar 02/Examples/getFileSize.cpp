#include <iostream>
#include <fstream>

size_t countSymbolsInFile(std::ifstream& ifs) {
	size_t initialPosition = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t symbolsCount = ifs.tellg();
	ifs.seekg(initialPosition);
	ifs.clear();
	return symbolsCount;
}

int getFileSize(const char* fileName) {
	if (!fileName) {
		return -1;
	}

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file " << fileName << '!';
		return -1;
	}

	return countSymbolsInFile(ifs);
}

int main() {
	std::cout << getFileSize("example.txt");
}
