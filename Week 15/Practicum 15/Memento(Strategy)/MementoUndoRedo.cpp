#include <iostream>
#include <string>
#include <memory>
#include <stack>
using namespace std;

// --- Memento Pattern: пример с undo/redo за текстов редактор

// Предварителна декларация на Editor (Originator)
class Editor;

// --- Клас Snapshot (Memento)
// Съхранява моментно състояние на Editor
class Snapshot {
    Editor* editor;        // указател към редактора, чието състояние пазим
    std::string text;      // текстово съдържание
    int x = 0, y = 0;       // позиция на курсора
    int width = 0;         // ширина на селекцията
public:
    // Конструктор: запазва копие на състоянието на редактора
    Snapshot(Editor* ed, std::string txt, int x, int y, int w)
        : editor(ed), text(std::move(txt)), x(x), y(y), width(w) {
    }

    // Възстановява редактора към запазеното състояние
    void restore();
};

// --- Клас Editor (Originator)
// Държи текущото състояние и може да го запише/възстанови
class Editor {
    std::string text;      // текущ текст
    int x = 0, y = 0;       // координати на курсора
    int width = 0;         // текуща ширина на селекцията
public:
    // Промяна на текста
    void setText(const std::string& t) {
        text = t;
    }
    // Позициониране на курсора
    void setCursor(int newX, int newY) {
        x = newX;
        y = newY;
    }
    // Задаване на ширината на селекцията
    void setSelectionWidth(int w) {
        width = w;
    }

    // Създава Memento (Snapshot) със сегашното състояние
    unique_ptr<Snapshot> createSnapshot() {
        return make_unique<Snapshot>(this, text, x, y, width);
    }

    // Показва текущото състояние в конзолата
    void printState() const {
        cout << "Text: \"" << text << "\" | "
            << "Cursor: (" << x << "," << y << ") | "
            << "SelW: " << width << "\n";
    }

    // Позволява на Snapshot да достъпва private полета
    friend class Snapshot;
};

// Реализация на restore(): връща редактора към запазеното състояние
void Snapshot::restore() {
    editor->setText(text);
    editor->setCursor(x, y);
    editor->setSelectionWidth(width);
}

// --- Клас History (Caretaker)
// Менажира две стека за undo и redo
class History {
    Editor& editor;   // референция към редактора
    stack<unique_ptr<Snapshot>> undoStack; // стек за Undo
    stack<unique_ptr<Snapshot>> redoStack; // стек за Redo
public:
    // Конструктор: асоциира с даден Editor
    History(Editor& ed) : editor(ed) {}

    // Запис на състоянието преди промяна
    // - добавя snapshot в undo стек
    // - изчиства redo стек (нови промени анулират възможността за redo)
    void backup() {
        undoStack.push(editor.createSnapshot());
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    // Undo: възстановява последното записано състояние
    // - премества текущото състояние в redo стек
    // - взима последния snapshot от undo стек и го възстановява
    void undo() {
        if (undoStack.empty()) return;
        redoStack.push(editor.createSnapshot());
        auto m = move(undoStack.top());
        undoStack.pop();
        m->restore();
    }

    // Redo: връща напред в историята
    // - премества текущото състояние в undo стек
    // - взима последния snapshot от redo стек и го възстановява
    void redo() {
        if (redoStack.empty()) return;
        undoStack.push(editor.createSnapshot());
        auto m = move(redoStack.top());
        redoStack.pop();
        m->restore();
    }
};

int main() {
    Editor editor;
    History history(editor);

    // 1) Начално състояние
    editor.setText("Start");
    editor.setCursor(0, 0);
    editor.setSelectionWidth(0);
    editor.printState();

    // 2) Първа промяна със запис
    history.backup();
    editor.setText("Hello");
    editor.setCursor(1, 5);
    editor.setSelectionWidth(3);
    editor.printState();

    // 3) Втора промяна със запис
    history.backup();
    editor.setText("World");
    editor.setCursor(2, 7);
    editor.setSelectionWidth(5);
    editor.printState();

    // 4) Undo два пъти
    cout << "\n-- undo --\n";
    history.undo(); 
    editor.printState();  // връщане към "Hello"
    history.undo(); 
    editor.printState();  // връщане към "Start"

    // 5) Redo веднъж
    cout << "\n-- redo --\n";
    history.redo(); 
    editor.printState();  // напред към "Hello"

    return 0;
}
