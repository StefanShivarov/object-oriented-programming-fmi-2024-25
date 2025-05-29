#include <iostream>
#include <string>

class User {
public:
    User(const std::string& username, unsigned age) : username(username), age(age) {}

    const std::string& getUsername() const {
        return username;
    }

    unsigned getAge() const {
        return age;
    }

private:
    std::string username;
    unsigned age;
};

// instead of having the user have multiple responsibilities to print himself or write himself to file,
// we can create a separate class that has serialization responsibility
// this way, the user class is only responsible for holding user data

class UserSerializer {
    std::ostream& os;
public:
    UserSerializer(std::ostream& os) : os(os) {}

    void serialize(const User& user) {
        os << user.getUsername() << " " << user.getAge() << std::endl;
    }
};

int main() {
    User stefo("Stefo", 21);
    UserSerializer serializer(std::cout);
    serializer.serialize(stefo);
}
