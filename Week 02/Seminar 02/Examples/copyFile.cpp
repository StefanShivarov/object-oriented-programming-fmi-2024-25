#include <iostream>
#include <fstream>

const int MAX_BUFF_SIZE = 1024;

// function returns bool to indicate whether the operation was successful or not
bool copyFile(const char* sourcePath, const char* destPath) {
	if (!sourcePath || !destPath) {
		return false;
	}

	std::ifstream ifs(sourcePath);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file " << sourcePath << '!';
		return false;
	}

	std::ofstream ofs(destPath);
	if (!ofs.is_open()) {
		std::cerr << "Failed to open file " << destPath << '!';
		return false;
	}

	while (!ifs.eof()) {
		char buff[MAX_BUFF_SIZE];
		ifs.getline(buff, MAX_BUFF_SIZE); // reads each line from source file
		ofs << buff << std::endl; // writes each line to the destination file
	}

	return true;
}

int main() {
	if (copyFile("example.txt", "copyOfExample.txt")) {
		std::cout << "Successfully copied file!";
	}
	else {
		std::cout << "Failed to copy file!";
	}
}
