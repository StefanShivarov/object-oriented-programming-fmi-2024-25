## RVO AND NRVO
```c++
#include <iostream>
using namespace std;
struct Teacher {
    int age = 5;
    Teacher() {
        std::cout << "Constructor\n";
    }

    Teacher(const Teacher& other) {
        age = other.age;
        std::cout << "Copy Constructor\n";

    }
    Teacher& operator=(const Teacher& other) {
        std::cout << "Operator =\n";
    }

    ~Teacher() {
        std::cout << "Destructor\n";
    }
};

Teacher createTeacher(bool flag) {
    Teacher t1;
    t1.age = 8;
    Teacher t2;
    if (flag) {
        return t1;  
    }
    return t2;
}
Teacher init() {
    Teacher t;
    t.age = 7;
    return t;
}

int main() {
    Teacher t = createTeacher(true);
    std::cout << t.age << std::endl;
}

```
