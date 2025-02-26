#include <iostream>
#include <fstream>
#include <sstream>
using std::endl;
using std::cout;
using std::cin;
constexpr int FIELD_MAX_SIZE = 50;
constexpr int MAX_COLUMN_SIZE = 7;
constexpr int MAX_ROWS_SIZE = 300;
constexpr int MAX_BUFFER_SIZE = 1024;
constexpr char DELIM = ',';
struct Field {
	char text[FIELD_MAX_SIZE];
	int size = 0;
};
struct Row {
	Field fields[MAX_COLUMN_SIZE];
	int columnSize = 0;
};
struct CsvTable {
	Row rows[MAX_ROWS_SIZE];
	int rowSize = 0;
};
void parseRow(Row& toReturn, const char* rowData) {
	std::stringstream ss(rowData);
	int index = 0;
	while (!ss.eof()) {
		ss.getline(toReturn.fields[index].text, MAX_BUFFER_SIZE, DELIM);
		toReturn.fields[index].size = strlen(toReturn.fields[index].text);
		index++;
	}
	toReturn.columnSize = index;
}
CsvTable parseTable(const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		return {};
	}
	CsvTable table;
	char buffer[MAX_BUFFER_SIZE];
	while (!ifs.eof()) {
		ifs.getline(buffer, MAX_BUFFER_SIZE);
		parseRow(table.rows[table.rowSize], buffer);
		table.rowSize++;
	}
	return table;
}
void printRow(const Row& row) {
	cout << row.fields[0].text;
	for (int i = 1; i < row.columnSize; i++) {
		cout << " | "<< row.fields[i].text;
	}
}
void printTable(const CsvTable& table) {
	for (int i = 0; i < table.rowSize; i++) {
		cout << i + 1 << " - ";
		printRow(table.rows[i]);
		cout << endl;
	}
}
void saveRow(std::ofstream& ofs, const Row& row) {
	ofs << row.fields[0].text;
	for (int i = 1; i < row.columnSize; i++) {
		ofs << DELIM<<row.fields[i].text;
	}
}
bool isEven(const Row& row) {
	int size = row.fields[1].size;
	return (row.fields[1].text[size - 1] - '0') % 2 == 0;
}
bool isOdd(const Row& row) {
	return !isEven(row);
}
void saveTable(const char* filename, const CsvTable& table,
	bool (*pred)(const Row& row) = [](const Row& row) {return true; }) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		return;
	}
	saveRow(ofs, table.rows[0]);
	ofs << endl;
	for (int i = 1; i < table.rowSize; i++) {
		if (pred(table.rows[i])) {
			saveRow(ofs, table.rows[i]);
			ofs << endl;
		}
		
	}
}
bool isGroup1(const Row& row) {
	return strcmp(row.fields[4].text, "Група 1 Поток 1") == 0;
}
void selectionSort(CsvTable& table) {
	for (int i = 1; i < table.rowSize; i++) {
		int minIndex = i;
		for (int j = i + 1; j < table.rowSize; j++) {
			if (strcmp(table.rows[j].fields[0].text, table.rows[minIndex].fields[0].text) < 0) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(table.rows[i], table.rows[minIndex]);
		}
	}
}
int main() {
	CsvTable table = parseTable("students.csv");
	selectionSort(table);
	printTable(table);
	saveTable("evenFn.csv", table, isEven);
	saveTable("oddFn.csv", table, isOdd);
	saveTable("Group1.csv", table, [](const Row& row) {
		return strcmp(row.fields[4].text, "Група 1 Поток 1") == 0;
		});
	saveTable("allStudents.csv", table);
}