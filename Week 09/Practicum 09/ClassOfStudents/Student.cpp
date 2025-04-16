#include "Student.h"

Student::Student(const MyString& name, size_t age): name(name),age(age)
{
    
}

Student::Student(MyString&& name, size_t age) : name(std::move(name)),age(std::move(age))
{
    
}

void Student::print() const
{
    std::cout << name << " " << age << std::endl;
}

const MyString& Student::getName() const
{
    return name;
}

size_t Student::getAge() const
{
    return age;
}
