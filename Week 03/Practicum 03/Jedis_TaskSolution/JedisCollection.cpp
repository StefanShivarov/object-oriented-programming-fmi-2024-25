#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
constexpr int MAX_NAME_SIZE = 50;
constexpr char DELIM = '|';
constexpr int MAX_COLORS = 5;
constexpr int MAX_TYPES = 3;
enum class Color {
	RED = 0,
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
	if (!name) {
		return {};
	}
	Jedi j;
	strcpy(j.name, name);
	j.age = age;
	j.power = power;
	j.saber = saber;
	return j;
}
Jedi createJedi(const char* name, unsigned age,
	unsigned power, const Color& color, const Type& type) {
	if (!name) {
		return {};
	}
	LightSaber saber = { color,type };
	return createJedi(name, age, power, saber);
}
const char* printColor(const Color& color) {
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
	return "UNKNOWN";

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
	return "UNKNOWN";
}
void printLightSaber(const LightSaber& saber) {
	cout << printColor(saber.color) << " ";
	cout << printType(saber.type);

}
void addJedi(JediCollection& collection, const Jedi& jedi) {
	collection.jedies[collection.jediSize++] = jedi;
}
int findJediIndex(const JediCollection& collection, const char* name) {
	if (!name) {
		return -1;
	}
	for (int i = 0; i < collection.jediSize; i++)
	{
		if (strcmp(collection.jedies[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}
void removeJedi(JediCollection& collection, const char* name) {
	if (!name) {
		return;
	}
	int index = findJediIndex(collection, name);
	if (index == -1) return;
	for (int i = index + 1; i < collection.jediSize; i++) {
		collection.jedies[i - 1] = collection.jedies[i];
	}
	collection.jediSize--;
}
void printJedi(const Jedi& jedi) {
	cout << jedi.name << " " << jedi.age << " " << jedi.power << " ";
	printLightSaber(jedi.saber);
}
void printJediCollection(const JediCollection& collection) {
	for (int i = 0; i < collection.jediSize; i++) {
		printJedi(collection.jedies[i]);
		cout << endl;
	}
}
void saveCollectionToBinary(const char* fileName, const JediCollection& collection) {
	if (!fileName) {
		return;
	}
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		return;
	}
	// можем да го направим така защото нямаме динамична памет и сме WRAP-NALI Джедаите в структура!!
	ofs.write((const char*)&collection, sizeof(collection));

}
JediCollection readCollectionFromBinary(const char* fileName) {
	if (!fileName) {
		return {};
	}
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) {
		return {};
	}
	JediCollection jd;
	ifs.read((char*)&jd, sizeof(JediCollection));
	return jd;
}
void saveLightSaber(std::ofstream& ofs, const LightSaber& saber) {
	ofs << (int)saber.color << DELIM;
	ofs << (int)saber.type;
}
void saveJedi(std::ofstream& ofs, const Jedi& jedi) {
	ofs << jedi.name << DELIM << jedi.age << DELIM << jedi.power << DELIM;
	saveLightSaber(ofs, jedi.saber);
}
void saveCollectionToTxt(const char* fileName, const JediCollection& collection) {
	if (!fileName) {
		return;
	}
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		return;
	}
	ofs << collection.jediSize;
	ofs << endl;
	for (int i = 0; i < collection.jediSize; i++) {
		saveJedi(ofs, collection.jedies[i]);
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
	if (!fileName) {
		return{};
	}
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
void sortByCriteria(JediCollection& collection, bool(*pred) (const Jedi&, const Jedi&)) {
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
void sortByPower(JediCollection& collection) {
	sortByCriteria(collection, [](const Jedi& j1, const Jedi& j2)
		{return j1.power < j2.power; });
}
void sortByAge(JediCollection& collection) {
	sortByCriteria(collection, [](const Jedi& j1, const Jedi& j2) {return j1.age < j2.age; });
}

Color mostPopularSaberColor(const JediCollection& collection) {
	int colorCount[MAX_COLORS] = { 0 };
	for (int i = 0; i < collection.jediSize; i++)
	{
		colorCount[(int)collection.jedies[i].saber.color]++;
	}
	int maxIndex = 0;
	int maxColor = 0;
	for (int i = 0; i < MAX_COLORS; i++)
	{
		if (colorCount[i] > maxColor) {
			maxColor = colorCount[i];
			maxIndex = i;
		}
	}
	return (Color)maxIndex;
}
Type mostPopularSaberType(const JediCollection& collection) {
	int typeCount[MAX_TYPES] = { 0 };
	for (int i = 0; i < collection.jediSize; i++)
	{
		typeCount[(int)collection.jedies[i].saber.type]++;
	}
	int maxIndex = 0;
	int maxType = 0;
	for (int i = 0; i < MAX_TYPES; i++)
	{
		if (typeCount[i] > maxType) {
			maxType = typeCount[i];
			maxIndex = i;
		}
	}
	return (Type)maxIndex;
}
int main() {
	{
		LightSaber lb;
		lb.color = Color::GREEN;
		lb.type = Type::DOUBLE_BLADED;
		Jedi j = createJedi("Ivan", 14, 1400, lb);
		Jedi j2 = createJedi("Georgi", 17, 140, Color::BLUE, Type::SINGLEBLADED);
		Jedi j3 = createJedi("Petur", 11, 150, Color::GREEN, Type::SINGLEBLADED);
		JediCollection collection;
		addJedi(collection, j);
		addJedi(collection, j2);
		addJedi(collection, j3);
		printJediCollection(collection);
		cout << (int)mostPopularSaberColor(collection) << endl;
		saveCollectionToBinary("jedi.dat", collection);
		saveCollectionToTxt("jedi.txt", collection);
		cout << "---------------------------------------SAVED" << endl;
	}
	{
		JediCollection collection = readCollectionFromBinary("jedi.dat");
		JediCollection collection2 = readCollectionToTxt("jedi.txt");
		printJediCollection(collection);
		cout << "---------------------------------------" << endl;
		printJediCollection(collection2);
	}
}