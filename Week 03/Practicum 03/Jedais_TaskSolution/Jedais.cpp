#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
constexpr int MAX_NAME_SIZE = 50;
constexpr char DELIM = '|';
enum class Color {
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE
};
enum class Type {
	SINGLEBLADED,
	DOUBLE_BLADED,
	CROSSGUARD
};
struct LightSaber {
	Color color;
	Type type;
};
struct Jedi {
	char name[MAX_NAME_SIZE];
	unsigned age;
	unsigned power;
	LightSaber saber;
};
constexpr int MAX_JEDI = 100;
struct JediCollection {
	Jedi jedies[MAX_JEDI];
	int jediSize = 0;
};
Jedi createJedi(const char* name, unsigned age, 
	unsigned power, const LightSaber& saber) {
	Jedi j;
	strcpy(j.name, name);
	j.age = age;
	j.power = power;
	j.saber = saber;
	return j;
}
Jedi createJedi(const char* name, unsigned age,
	unsigned power, const Color& color, const Type& type) {
	LightSaber saber = { color,type };
	return createJedi(name, age, power, saber);
}
const char * printColor(const Color& color) {
	if (Color::BLUE == color) {
		return "BLUE";
	}
	if (color == Color::GREEN) {
		return "Green";
	}
	if (color == Color::PURPLE) {
		return "Purple";
	}
	if (color == Color::YELLOW) {
		return "YELLOW";
	}
	if (color == Color::RED) {
		return "RED";
	}
	
}
const char* printType(const Type& type) {
	if (type == Type::CROSSGUARD) {
		return "CROSSGUARD";
	}
	if (type == Type::SINGLEBLADED) {
		return "SINGLEBLADED";
	}
	if (type == Type::DOUBLE_BLADED) {
		return "DOUBLE_BLADED";
	}
}
void printLightSaber(const LightSaber& saber) {
	cout << printColor(saber.color)<<" ";
	cout << printType(saber.type);

}
void addJedi(JediCollection& collection, const Jedi& jedi) {
	collection.jedies[collection.jediSize++] = jedi;
}
int findJediIndex(const JediCollection& collection, const char* name) {
	for (int i = 0; i < collection.jediSize; i++)
	{
		if (strcmp(collection.jedies[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}
void removeJedi(JediCollection& collection, const char* name) {
	int index = findJediIndex(collection, name);
	for (int i = index + 1; i < collection.jediSize; i++) {
		collection.jedies[i - 1] = collection.jedies[i];
	}
	collection.jediSize--;
}
void printJedi(const Jedi& jedi) {
	cout << jedi.name << " " << jedi.age << " " << jedi.power<<" ";
	printLightSaber(jedi.saber);
}
void printJediCollection(const JediCollection& collection) {
	for (int i = 0; i < collection.jediSize; i++) {
		printJedi(collection.jedies[i]);
		cout << endl;
	}
}
void saveCollectionToBinary(const char* fileName, const JediCollection& collection) {
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		return;
	}
	// можем да го направим така защото нямаме динамична памет и сме WRAP-NALI Джедаите в структура!!
	ofs.write((const char*)&collection, sizeof(collection));
	
}
JediCollection readCollectionFromBinary(const char* fileName) {
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return {};
	}
	JediCollection jd;
	ifs.read((char*)&jd, sizeof(JediCollection));
}
void saveLightSaber(std::ofstream& ofs, const LightSaber& saber) {
	ofs << (int)saber.color << DELIM;
	ofs << (int)saber.type;
}
void saveJedi(std::ofstream& ofs, const Jedi& jedi) {
	ofs << jedi.name<<DELIM<<jedi.age<<DELIM<<jedi.power<<DELIM;
	saveLightSaber(ofs,jedi.saber);
}
void saveCollectionToTxt(const char* fileName, const JediCollection& collection) {
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		return;
	}
	ofs << collection.jediSize;
	ofs << endl;
	for (int i = 0; i < collection.jediSize; i++){
		saveJedi(ofs,collection.jedies[i]);
		ofs << endl;
	}
}
void readLightSaber(std::ifstream& ifs, LightSaber& saber) {
	int color, type;
	
	ifs >> color;
	saber.color = Color(color);
	ifs.ignore();
	ifs >> type;
	saber.type = Type(type);
}
void readJedi(std::ifstream& ifs, Jedi& jedi) {
	ifs.getline(jedi.name, 1024, DELIM);
	ifs >> jedi.age;
	ifs.ignore();
	ifs >> jedi.power;
	ifs.ignore();
	readLightSaber(ifs, jedi.saber);
}

JediCollection readCollectionToTxt(const char* fileName) {
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return {};
	}
	JediCollection collection;
	ifs >> collection.jediSize;
	ifs.ignore();
	for (int i = 0; i < collection.jediSize; i++)
	{
		readJedi(ifs, collection.jedies[i]);
		ifs.ignore();
	}
	return collection;
}
bool sortByPower(const Jedi& j1, const Jedi& j2) {
	return j1.power < j2.power;
}
bool sortByAge(const Jedi& j1, const Jedi& j2) {
	return j1.age < j2.age;
}
void sortBy(JediCollection& collection, bool(*pred) (const Jedi&, const Jedi&)) {
	for (int i = 0; i < collection.jediSize; i++) {
		int minIndex = i;
		for (int j = i + 1; j < collection.jediSize; j++) {
			if (pred(collection.jedies[j], collection.jedies[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			std::swap(collection.jedies[i], collection.jedies[minIndex]);
		}
	}
}
int main() {
	{
		LightSaber lb;
		lb.color = Color::GREEN;
		lb.type = Type::DOUBLE_BLADED;
		Jedi j = createJedi("Ivan", 14, 1400, lb);
		Jedi j2 = createJedi("Georgi", 17, 140, Color::BLUE, Type::SINGLEBLADED);
		JediCollection collection;
		addJedi(collection, j);
		addJedi(collection, j2);
		printJediCollection(collection);
		saveCollectionToBinary("jedi.dat", collection);
		saveCollectionToTxt("jedi.txt", collection);
	}
	{
		JediCollection collection = readCollectionFromBinary("jedi.dat");
		JediCollection collection2 = readCollectionToTxt("jedi.txt");
		printJediCollection(collection);
		cout << "---------------------------------------" << endl;
		printJediCollection(collection2);
	}
}