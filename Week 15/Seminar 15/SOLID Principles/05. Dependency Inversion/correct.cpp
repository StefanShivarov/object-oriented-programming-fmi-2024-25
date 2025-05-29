#include <iostream>
#include <string>

// Abstraction
class DatabaseConnector {
public:
    virtual void connect() = 0;
    virtual void query(const std::string& sql) = 0;
    virtual ~DatabaseConnector() = default;
};

// MySQL Implementation
class MySqlDatabaseConnector : public DatabaseConnector {
public:
    void connect() override {
        std::cout << "[MySQL] Connecting to MySQL database...\n";
    }

    void query(const std::string& sql) override {
        std::cout << "[MySQL] Executing query: " << sql << "\n";
    }
};

class PostgreSqlDatabaseConnector : public DatabaseConnector {
public:
    void connect() override {
        std::cout << "[PostgreSQL] Connecting to PostgreSQL database...\n";
    }

    void query(const std::string& sql) override {
        std::cout << "[PostgreSQL] Executing query: " << sql << "\n";
    }
};

class MongoDbConnector : public DatabaseConnector {
public:
    void connect() override {
        std::cout << "[MongoDB] Connecting to MongoDB database...\n";
    }

    void query(const std::string& command) override {
        std::cout << "[MongoDB] Executing command: " << command << "\n";
    }
};

class UserRepository {
public:
    explicit UserRepository(std::shared_ptr<DatabaseConnector> connector)
        : db(connector) {}

    void fetchAllUsers() {
        db->query("SELECT * FROM users");
    }

    void addUser(const std::string& name) {
        db->query("INSERT INTO users (name) VALUES ('" + name + "')");
    }

private:
    std::shared_ptr<DatabaseConnector> db;
};
