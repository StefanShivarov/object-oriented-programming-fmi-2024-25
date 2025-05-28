#include <iostream>
#include <string>
#include <vector>

// --- Memento: пази състоянието на Originator без да му гледа вътре
class Memento {
    friend class Originator;        // само Originator може да чете state_
    std::string state_;
    Memento(const std::string& state) : state_(state) {}
public:
    // Ако искаме, можем да дадем публичен геттер, но не е задължително
    std::string getState() const { return state_; }
};

// --- Originator: обектът, чието състояние запазваме/възстановяваме
class Originator {
    std::string state_;
public:
    void setState(const std::string& state) {
        state_ = state;
        std::cout << "Originator: Setting state to " << state_ << "\n";
    }
    std::string getState() const {
        return state_;
    }
    // Създава Мементо с текущото състояние
    Memento saveToMemento() const {
        std::cout << "Originator: Saving to Memento.\n";
        return Memento(state_);
    }
    // Връща се в предишно състояние от Мементо-то
    void restoreFromMemento(const Memento& m) {
        state_ = m.state_;
        std::cout << "Originator: State after restoring from Memento: "
            << state_ << "\n";
    }
};

// --- Caretaker: пази история от Мемента-та, но не може да ги променя
class Caretaker {
    std::vector<Memento> history_;
public:
    void addMemento(const Memento& m) {
        history_.push_back(m);
    }
    // Връща копие на memento-то от историята
    Memento getMemento(size_t index) const {
        return history_.at(index);
    }
};

int main() {
    Originator origin;
    Caretaker caretaker;

    origin.setState("Foo");
    caretaker.addMemento(origin.saveToMemento());

    origin.setState("Bar");
    caretaker.addMemento(origin.saveToMemento());

    // Undo
    origin.restoreFromMemento(caretaker.getMemento(0));
    // Redo
    origin.restoreFromMemento(caretaker.getMemento(1));
    return 0;
}
