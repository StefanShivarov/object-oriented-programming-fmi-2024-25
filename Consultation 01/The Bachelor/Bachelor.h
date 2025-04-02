#pragma once
#include <ostream>

#include "Lady.h"

enum class EyeColour {
    BROWN,
    BLUE,
    GREEN,
    HAZEL, // iykyk
    GREY,
    UNKNOWN
};

class Bachelor {
public:
    Bachelor() = default;
    Bachelor(const char* name, unsigned age);
    Bachelor(const char* name, unsigned age, const char* profession);
    Bachelor(const char* name, unsigned age, const char* profession, const char* phrase);
    Bachelor(const char* name, unsigned age, const char* profession, const char* phrase, EyeColour eyeColour);

    Bachelor(const Bachelor& other);
    Bachelor& operator=(const Bachelor& other);

    ~Bachelor();

    const char* getName() const;
    void setName(const char* name);

    const char* getProfession() const;
    void setProfession(const char* profession);

    const char* getPhrase() const;
    void setPhrase(const char* phrase);

    unsigned getAge() const;
    void setAge(unsigned age);

    EyeColour getEyeColour() const;
    void setEyeColour(EyeColour eyeColour);

    bool giveRoseTo(Lady& lady);

    void serialize(std::ostream& os) const;

private:
    char* name = nullptr;
    char* profession = nullptr;
    char* phrase = nullptr;
    unsigned age = 0;
    EyeColour eyeColour = EyeColour::UNKNOWN;

    void free();
    void copyFrom(const Bachelor& other);
};
