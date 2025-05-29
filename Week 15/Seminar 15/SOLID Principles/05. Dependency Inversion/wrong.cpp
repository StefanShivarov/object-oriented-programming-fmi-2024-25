#include <iostream>
#include <string>

class MySqlDatabaseConnector {
public:
    void connect() {
        std::cout << "[MySQL] Connecting to MySQL database...\n";
    }

    void query(const std::string& sql) {
        std::cout << "[MySQL] Executing query: " << sql << "\n";
    }
};

class UserRepository {
public:
    explicit UserRepository(std::shared_ptr<MySqlDatabaseConnector> connector)
        : db(connector) {}

    void fetchAllUsers() {
        db->query("SELECT * FROM users");
    }

    void addUser(const std::string& name) {
        db->query("INSERT INTO users (name) VALUES ('" + name + "')");
    }

private:
    std::shared_ptr<MySqlDatabaseConnector> db;
};
