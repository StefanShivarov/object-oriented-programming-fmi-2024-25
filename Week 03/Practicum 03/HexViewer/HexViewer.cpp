#include <iostream>
#include <fstream>
using std::endl;
using std::cout;
using std::cin;

struct HexViewer {
	unsigned char* data;
	int size = 0;
};

int getFileSize(std::ifstream& ifs) {
	int currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(currPos);
	return size;
}
HexViewer init(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) {
		return {};
	}
	HexViewer hex;
	hex.size = getFileSize(ifs);
	hex.data = new unsigned char[hex.size]; // must be deleted
	ifs.read((char*)hex.data, hex.size);
	return hex;
}
bool isValidSymbol(unsigned char ch) {
	return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z';
}
void byteToHex(unsigned char ch, char hexData[3]) {
	int delim = ch / 16;
	int remainder = ch % 16;
	hexData[0] = delim >= 10 ? (delim - 10 + 'A') : delim + '0';
	hexData[1] = remainder >= 10 ? (remainder - 10 + 'A') : remainder + '0';
	hexData[2] = '\0';
}
void print(const HexViewer& hex) {

	for (int i = 0; i < hex.size; i++) {
		char hexData[3];
		byteToHex(hex.data[i], hexData);
		cout << hexData << " ";
		//cout << std::hex << (int)hex.data[i]<<" ";
	}


	for (int i = 0; i < hex.size; i++) {
		if (isValidSymbol(hex.data[i])) {
			cout << hex.data[i];
		}
		else {
			cout << ".";
		}

	}
}

void freeHexViewer(HexViewer& hx) {
	delete[] hx.data;
	hx.size = 0;
}
void changeByteAtIndex(const char* filename, int index, char ch) {
	std::fstream ofs(filename, std::ios::binary |
		std::ios::out | std::ios::in | std::ios::ate);
	if (!ofs.is_open()) {
		return;
	}
	ofs.seekp(index, std::ios::beg);
	ofs.write((char*)&ch, sizeof(ch));
}
int main() {
	//changeByteAtIndex("students.dat", 1, 'f');
	HexViewer hex = init("students.dat"); // use any binary file you have written to and check it out with the hex viewer

	print(hex);
	freeHexViewer(hex);
}