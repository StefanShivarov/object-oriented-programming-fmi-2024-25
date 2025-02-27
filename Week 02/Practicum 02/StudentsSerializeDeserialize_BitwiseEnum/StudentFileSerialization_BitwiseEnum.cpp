
#include <iostream>
#include <fstream>
using std::endl;
using std::cout;
constexpr int MAX_NAME_LENGTH = 100;
constexpr char DELIM = '|';
typedef unsigned char byte;
enum class Electives : byte {
	OOPPRAKT = 1<<0, 
	UPPRAKT = 1<<1, 
	Java = 1<<2,
	IO = 1<<3
};
struct Student {
	char name[MAX_NAME_LENGTH];
	int fn;
	byte elective = 0;
};
constexpr int MAX_STUDENT_SIZE = 10;
struct StudentDB {
	Student student[MAX_STUDENT_SIZE];
	int studentSize = 0;
};

void sereializeStudent(std::ofstream& ofs,const Student& st) {
	ofs << st.name << DELIM << st.fn << DELIM << st.elective;
	ofs << endl;
}
void serializeDatabase(std::ofstream& ofs, const StudentDB& db) {

	ofs << db.studentSize;
	ofs << endl;
	for (int i = 0; i < db.studentSize; i++) {
		sereializeStudent(ofs,db.student[i]);
	}

}
Student deserializeStudent(std::ifstream& ifs) {
	Student st;
	ifs.ignore();
	ifs.getline(st.name, MAX_NAME_LENGTH, DELIM);
	ifs >> st.fn;
	ifs.ignore();
	st.elective = ifs.get();
	return st;
}
StudentDB deserializeStudentDB(std::ifstream& ifs) {

	StudentDB db;
	ifs >> db.studentSize;
	for (int i = 0; i < db.studentSize; i++) {
		db.student[i] = deserializeStudent(ifs);
	}
	return db;
}
void addElective(Student& st, Electives elective) {
	st.elective |= (byte)elective;
}
void removeElective(Student& st, Electives elective) {
	st.elective &= (~(byte)elective);
}
void printStudent(const Student& st) {
	cout << st.name << " " << st.fn;
}
const char* byteToElective(byte mask) {
	switch (mask) {
	case 1 << 0: {
		return "OOPPRAKT";
	}
	case 1 << 1: {
		return "UPPRAKT";
	}
	case 1 << 2: {
		return "JAVA";
	}
	case 1 << 3: {
		return "IO";
	}
	default: {
		return "No Electives";
	}
	}
}
void printElective(const Student& st) {
	for (int i = 0; i < 4; i++) {
		byte mask = 1 << i;
		if (mask & st.elective) {
			cout << " " << byteToElective(mask);
		}
	}
}
void printDatabase(const StudentDB& db) {
	for (int i = 0; i < db.studentSize; i++) {
		printStudent(db.student[i]);
		printElective(db.student[i]);
		cout << endl;
	}
}

int main()
{
	{
		std::ofstream ofs("studentsFile.txt");
		if (!ofs.is_open()) {
			return -1;
		}
		StudentDB db = {
			{
				{"kiril petkov",123},
				{"ivan ivanov",321},
				{"georgi georgiev",372}
			},
			3
		};
		addElective(db.student[0], Electives::OOPPRAKT);
		addElective(db.student[0], Electives::UPPRAKT);
		addElective(db.student[1], Electives::Java);
		addElective(db.student[1], Electives::IO);
		serializeDatabase(ofs, db);

	}// calls  ofs.close()
	{
		std::ifstream ifs("studentsFile.txt");
		if (!ifs.is_open()) {
			return -1;

		}
		StudentDB db = deserializeStudentDB(ifs);
		cout << db.studentSize<<endl;
		printDatabase(db);
	}// calls  ifs.close()
}

