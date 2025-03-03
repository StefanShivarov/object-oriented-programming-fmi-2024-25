#include <iostream>
#include <fstream>
using std::endl;
using std::cout;
void replaceText(const char* fileName1, const char* fileName2, const char* oldWord, const char* newWord) {
	std::ifstream ifs(fileName1);
	if (!ifs.is_open()) {
		return;
	}
	std::ofstream ofs(fileName2);
	if (!ofs.is_open()) {
		return;
	}
	while (!ifs.eof()) {
		char buffer[1024];
		ifs >> buffer;
		if (strcmp(buffer, oldWord) == 0) {
			ofs << newWord;
		}
		else {
			ofs << buffer;
		}
		ofs << " ";
		if (ifs.peek() == '\n') {
			ofs << endl;
			ifs.ignore();
		}
	}
}

int main() {
	replaceText("file1.txt", "file3.txt", "OOP", "DSTR");
}