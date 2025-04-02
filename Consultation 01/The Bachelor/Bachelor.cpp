#include "Bachelor.h"
#include <cstring>
#pragma warning(disable:4996)

namespace {
    void copyDynamicCharArray(char*& dest, const char* src) {
        if (src == nullptr || src == dest) {
            return;
        }
        delete[] dest;
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }

    const char* convertEyeColourToString(EyeColour eyeColour) {
        using enum EyeColour;
        switch (eyeColour) {
            case BROWN: return "Brown";
            case BLUE: return "Blue";
            case GREEN: return "Green";
            case HAZEL: return "Hazel";
            case GREY: return "Grey";
            default: return "Unknown";
        }
    }
}

Bachelor::Bachelor(const char* name, unsigned age) {
    setName(name);
    setAge(age);
}

Bachelor::Bachelor(const char* name, unsigned age, const char* profession) : Bachelor(name, age) {
    setProfession(profession);
}

Bachelor::Bachelor(const char* name, unsigned age, const char* profession, const char* phrase) : Bachelor(name, age, profession) {
    setPhrase(phrase);
}

Bachelor::Bachelor(const char* name, unsigned age, const char* profession, const char* phrase, EyeColour eyeColour) : Bachelor(name, age, profession, phrase) {
    setEyeColour(eyeColour);
}

Bachelor::Bachelor(const Bachelor& other) {
    copyFrom(other);
}

Bachelor& Bachelor::operator=(const Bachelor& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Bachelor::~Bachelor() {
    free();
}

const char* Bachelor::getName() const {
    return name;
}

void Bachelor::setName(const char* name) {
    copyDynamicCharArray(this->name, name);
}

unsigned Bachelor::getAge() const {
    return age;
}

void Bachelor::setAge(unsigned age) {
    if (age > 120 || age < 18) {
        return;
    }
    this->age = age;
}

const char* Bachelor::getProfession() const {
    return profession;
}

void Bachelor::setProfession(const char* profession) {
    copyDynamicCharArray(this->profession, profession);
}

const char* Bachelor::getPhrase() const {
    return phrase;
}

void Bachelor::setPhrase(const char* phrase) {
    copyDynamicCharArray(this->phrase, phrase);
}

EyeColour Bachelor::getEyeColour() const {
    return eyeColour;
}

void Bachelor::setEyeColour(EyeColour eyeColour) {
    this->eyeColour=eyeColour;
}

bool Bachelor::giveRoseTo(Lady& lady) {
    return lady.receiveRose(this);
}

void Bachelor::serialize(std::ostream& os) const {
    os << name << ' ' << age << ' ' << profession << ' ' << phrase << convertEyeColourToString(eyeColour);
}

void Bachelor::free() {
    delete[] name;
    name = nullptr;
    delete[] profession;
    profession = nullptr;
    delete[] phrase;
    phrase = nullptr;
    age = 0;
}

void Bachelor::copyFrom(const Bachelor& other) {
    copyDynamicCharArray(name, other.name);
    copyDynamicCharArray(profession, other.profession);
    copyDynamicCharArray(phrase, other.phrase);
    age = other.age;
    eyeColour = other.eyeColour;
}
