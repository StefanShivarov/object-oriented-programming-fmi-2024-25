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
	int oldWordSize = strlen(oldWord);
	int wordIndex = 0;
	while (true) {
		char currenCh = ifs.get();
		if (ifs.eof()) {
			break;
		}
		if(currenCh == oldWord[wordIndex]) {
			wordIndex++;
			if (oldWordSize == wordIndex) {
				ofs << newWord;
				wordIndex = 0;
			}
			continue;
		}
		else {
			for (int i = 0; i < wordIndex; i++) {
				ofs << oldWord[i];
			}
			ofs << currenCh;
			wordIndex = 0;
		}
	}
}
int main() {
	replaceText("file1.txt", "file3.txt", "OOP", "DUPRSHIT");
}