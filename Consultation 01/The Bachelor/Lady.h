#pragma once
#include <iostream>

class Bachelor;

class Lady {
public:
    Lady() = default;
    Lady(const char* name, unsigned age);
    Lady(const char* name, unsigned age, Bachelor* bachelor);

    Lady(const Lady& other);
    Lady& operator=(const Lady& other);

    ~Lady();

    const char* getName() const;
    void setName(const char* name);

    unsigned getAge() const;
    void setAge(unsigned age);

    bool isEliminated() const;
    void setEliminated(bool flag);

    unsigned getRosesCount() const;

    bool receiveRose(Bachelor* bachelor);

    const Bachelor* getFavouriteBachelor() const;
    void setFavouriteBachelor(Bachelor* bachelor);

    void serialize(std::ostream& os) const;

private:
    char* name = nullptr;
    unsigned age = 0;
    unsigned rosesCount = 0;
    Bachelor* favouriteBachelor = nullptr;
    bool eliminated = false;

    void free();
    void copyFrom(const Lady& other);
};
