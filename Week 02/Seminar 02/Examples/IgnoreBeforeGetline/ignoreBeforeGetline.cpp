#include <iostream>
#include <fstream>

constexpr int MAX_BUFF_SIZE = 1024;

using std::cerr;
using std::cout;
using std::endl;

int main() {
	std::ifstream ifs("ignore.txt");
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file!";
		return -1;
	}

	char buff[MAX_BUFF_SIZE];
	ifs >> buff; // formatted input will read until the first whitespace, which in this case is '\n'
	cout << buff << endl; // this will print: stefoto
	
	ifs.ignore(); // try to run the code with this line and without this line, to see the difference!
	
	ifs.getline(buff, MAX_BUFF_SIZE); // 
	cout << buff << endl; // If we use ifs.ignore() it will move the get pointer after '\n'
						  // and it will print : "e momche za vsichko".
						  // If we don't it will print an empty string, because the get pointer will be at \n
						  // and it will try to perform getline on '\n', which will result in an empty string
}
