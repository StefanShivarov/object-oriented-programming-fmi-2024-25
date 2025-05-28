#include <iostream>
#include <fstream>
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

    void print() const {
        std::cout << username << " " << age << std::endl;
    }

    void saveToTextFile(std::ofstream& os) const {
        os << username << " " << age << std::endl;
    }

private:
    std::string username;
    unsigned age;
};

// notice how the user is forced to have responsibilites to print himself and save himself to a text file
// this disobeys the single responsibility principle
// the user's responisibility is solely to be a user, not a printer or a filewriter

int main() {
    User user("abcdef", 90);
    user.print(); // this is not a good design
}
