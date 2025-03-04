# 03. Двоични файлове

При двоични файлове зползваме функциите:

1. `read(char* memoryBlock, size_t size);`
2. `write(const char* memoryBlock, size_t size);`

Обърнете внимание, че функцията приема `char*`. Ако искаме да запазим променлива от друг вид, ще трябва експлицитно да преобразуваме указателя към тип `char*` (без значение, че указателят не сочи към елементи от тип char)

### Пример за писане в двоичен файл:

```c++
#include <iostream>
#include <fstream>

namespace Constants {
	constexpr char FILE_NAME[] = "file.dat";
};

int main() {
	std::ofstream out(Constants::FILE_NAME, std::ios::binary);

	int a = 155555;
	out.write((const char*)&a, sizeof(a));

	out.close();
}
```

### Пример за четене от двоичен файл:

```c++
#include <iostream>
#include <fstream>

namespace Constants {
	constexpr char FILE_NAME[] = "file.dat";
};

int main() {
	std::ifstream in(Constants::FILE_NAME, std::ios::binary);

	int a;
	in.read((char*)&a, sizeof(int));

	std::cout << a << std::endl;

	in.close();
}
```

### Съдържанието на двоичния файл:

![Binary file example](https://i.ibb.co/G3R72qG/sudurjanie.png "Binary file example")

Байтовете се записват в **обратна посока**. Най-старшият байт е последен. Следователно запаметеното число е **00025fa3**, което е точно шестнайсетичният запис на числото **155555**.

### Примери за запазване на структури във файл.

- запазване на структура, която не използва динамична памет

```c++
#include <iostream>
#include <fstream>

namespace Constants {
	constexpr char FILE_NAME[] = "testObj.bat";
};

struct Test {
	bool b;
	int x;
};

int main() {
	{
		Test t = { true, 45 };
		std::ofstream file(Constants::FILE_NAME, std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.write((const char*)&t, sizeof(t));
	}

	{
		Test t;
		std::ifstream file(Constants::FILE_NAME, std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.read((char*)&t, sizeof(t));
		std::cout << t.b << " " << t.x << std::endl;
	}
}
```

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)


namespace Constants {
	constexpr char FILE_NAME[] = "testObj.bat";
	constexpr int NAME_SIZE = 25;
};

struct Student {
	char name[Constants::NAME_SIZE];
	int fn;
	int age;
};

int main() {
	{
		Student st;
		strcpy(st.name, "Ivan");
		st.fn = 1234;
		st.age = 33;

		std::ofstream file(Constants::FILE_NAME, std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while writing to binary file!" << std::endl;
			return -1;
		}

		//since the data is grouped in the struct, we can save it like this.
		file.write((const char*)&st, sizeof(st));
	}

	{
		Student st;
		std::ifstream file(FILE_NAME, std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while reading from binary file!" << std::endl;
			return -1;
		}

		file.read((char*)&st, sizeof(st));
		std::cout << st.name << " " << st.fn << " " << st.age << std::endl;
	}
}
```

---

- запазване на структура, която използва динамична памет

```c++
#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)


namespace Constants {
	constexpr char FILE_NAME[] = "students.dat";
};

struct Student {
	int fn;
	int gradesCount;
	char* name;
	double averageGrade;
};

Student createStudent(const char* name, int fn, int gradesCount, double avGrade) {
	Student obj;

	size_t nameLen = strlen(name);

	obj.name = new char[nameLen + 1];
	strcpy(obj.name, name);

	obj.fn = fn;
	obj.gradesCount = gradesCount;
	obj.averageGrade = avGrade;

	return obj;
}

void saveStudentToFile(ofstream& f, const Student& st) {
	size_t nameLen = strlen(st.name);

	f.write((const char*)&nameLen, sizeof(nameLen));  //first we write the size of the name!
	f.write(st.name, nameLen);

	f.write((const char*)&st.fn, sizeof(st.fn));
	f.write((const char*)&st.gradesCount, sizeof(st.gradesCount));
	f.write((const char*)&st.averageGrade, sizeof(st.averageGrade));

}

Student readStudentFromFile(ifstream& f) {
	Student res;

	size_t nameLen;

	f.read((char*)&nameLen, sizeof(nameLen)); //first we read the size of the name!

	res.name = new char[nameLen + 1];
	f.read(res.name, nameLen);
	res.name[nameLen] = '\0';

	f.read((char*)&res.fn, sizeof(res.fn));
	f.read((char*)&res.gradesCount, sizeof(res.gradesCount));
	f.read((char*)&res.averageGrade, sizeof(res.averageGrade));

	return res;
}

void freeStudent(Student& s) {
	delete[] s.name;
	s.averageGrade = s.fn = s.gradesCount = 0;
}

void print(const Student& st) {
	std::cout << st.name << " " << st.fn << " " << st.gradesCount << " " << st.averageGrade << std::endl;
}

int main() {
	{
		Student s1 = createStudent("Ivan", 1234, 2, 4);
		Student s2 = createStudent("Petur", 5555, 5, 5.5);

		std::ofstream f1(Constants::FILE_NAME, std::ios::binary);

		if (!f1.is_open()) {
			cout << "Error" << endl;
			return -1;
		}

		saveStudentToFile(f1, s1);
		saveStudentToFile(f1, s2);

		freeStudent(s1);
		freeStudent(s2);
	}

	{
		std::ifstream f2(Constants::FILE_NAME, std::ios::binary);

		if (!f2.is_open()) {
			cout << "Error" << endl;
			return -1;
		}

		Student s1 = readStudentFromFile(f2);
		Student s2 = readStudentFromFile(f2);

		print(s1);
		print(s2);

		freeStudent(s1);
		freeStudent(s2);
	}
}
```

### Пример за запазване на масив от структури във файл.

- запазване на масив от обекти, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)


namespace Constants {
	constexpr char FILE_NAME[] = "students.dat";
	constexpr int NAME_SIZE[] = 30;
};

struct Student {
	char name[Constants::NAME_SIZE];
	int age;
	int fn;
};

void initStudent(Student& st, const char* name, int age, int fn) {
	strcpy(st.name, name);
	st.age = age;
	st.fn = fn;
}

void saveToFile(const Student* students, size_t count, ofstream& file) {
	file.write((const char*)students, count * sizeof(Student));
}

int main() {
	Student* arr = new Student[4];
	initStudent(arr[0], "ivan", 44, 1234);
	initStudent(arr[1], "petur", 12, 765);
	initStudent(arr[2], "alex", 15, 44);
	initStudent(arr[3], "katerina", 19, 12134);

	std::ofstream file(Constants::FILE_NAME, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening the file!" << std::endl;
		delete[] arr; //!
		return -1;
	}

	saveToFile(arr, 4, file);

	delete[] arr;
}
```

---

- четене на масив от обекти, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>

namespace Constants {
	constexpr char FILE_NAME[] = "students.dat";
	constexpr int NAME_SIZE[] = 30;
};

struct Student {
	char name[Constants::NAME_SIZE];
	int age;
	int fn;
};

size_t getFileSize(ifstream& f) {
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void readFromFile(Student*& ptr, size_t& studentsCount, ifstream& f) {
	size_t sizeOfFile = getFileSize(f);
	studentsCount = sizeOfFile / sizeof(Student);
	ptr = new Student[studentsCount];
	f.read((char*)ptr, sizeOfFile);
}

int main() {
	Student* arr;
	size_t count;
	std::ifstream file(Constants::FILE_NAME, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	readFromFile(arr, count, file);

	for (int i = 0; i < count; i++) {
		std::cout << "Name: " << arr[i].name << ", age: " << arr[i].age << ", fn: " << arr[i].fn << std::endl;
	}

	delete[] arr;
}
```

### Подравняване

```c++
#include <iostream>
#include <fstream>

namespace Constants {
	constexpr FILE_NAME[] = "output.dat";
};

struct Test {
 	char ch;
 	int a;
};

int main() {
    std::ofstream f(Constants::FILE_NAME, std::ios::binary);

    if(!f.is_open()) {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    Test arr[3] = {{'a', 400},{'b', 500},{'c', 600}};

    f.write((const char*)&arr, sizeof(arr));

    f.close();
}
```

След изпълнението на програмата, файлът (**output.dat**) изглежда така:

![Image of the binary file after running the code](https://i.ibb.co/0JthLd6/3-A978-D14-7-C7-A-4-ABD-8-B0-C-DA27-F6-E9-CD0-A.png "Binary file")

---

_Credits: [Georgi Terziev](https://github.com/GeorgiTerziev02/)_
