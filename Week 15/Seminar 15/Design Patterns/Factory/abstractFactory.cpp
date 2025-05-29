#include <iostream>

class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() = default;
};

class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows Button" << std::endl;
    }
};

class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac Button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows Checkbox" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac Checkbox" << std::endl;
    }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WindowsButton();
    }
    Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacButton();
    }
    Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};

void renderUI(GUIFactory* factory) {
    Button* btn = factory->createButton();
    Checkbox* cb = factory->createCheckbox();

    btn->render();
    cb->render();

    delete btn;
    delete cb;
}

int main() {
    GUIFactory* factory;

    bool isWindows = true;

    if (isWindows) {
        factory = new WindowsFactory();
    } else {
        factory = new MacFactory();
    }

    renderUI(factory);

    delete factory;
    return 0;
}
