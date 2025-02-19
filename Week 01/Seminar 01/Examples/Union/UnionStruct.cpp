#include <iostream>
using std::cout;
using std::endl;
struct Person {
	char name[10];
	int age;
};
struct Student {
	char name[10];
	int age;
	int grade;
};
union MyUnion
{
	Person person;
	Student student;
};

int main()
{
	Person person = { "Georgi",12 };
	Student student = { "Ivan", 14,6 };
	MyUnion uni;
	uni.person = person;
	uni.student = student;
	cout << uni.student.name<<endl;
	cout << uni.person.name << endl;
}