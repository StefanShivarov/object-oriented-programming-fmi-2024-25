#include "Vector.hpp"
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	Vector<int> v;
	v.pushBack(5);
	v.pushBack(2);
	for (auto it = v.rbegin(); it != v.rend(); it++) {
		cout << (*it)<<endl;
	}
	for (auto& it : v) {
		cout << (it) << endl;
	}
}