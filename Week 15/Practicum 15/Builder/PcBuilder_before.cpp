#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class Computer {

private:
    //mandatory
    size_t sdd = 0;
    size_t ram = 0;
    //optional parameters
    bool is_graphics_card_avaible = false;
    bool is_bluetooth_avaible = false;
    size_t diskId = 0;

public:

    Computer(size_t sdd, size_t ram, bool isBavaible = false, bool isGavaible = false, size_t diskId=0) : sdd(sdd),
     ram(ram),
      is_bluetooth_avaible(isBavaible),
      is_graphics_card_avaible(isGavaible),
     diskId(diskId)
    {

    }

    //setters
     void setGraphicCard(bool b) {
        is_graphics_card_avaible = b;
     }
    void setBluetooth(bool b) {
        is_bluetooth_avaible = b;
    }
    void setDiskId(size_t id) {
        if (id > 100) {
            throw 221;
        }
        diskId = id;
    }
    //getters
    size_t get_sdd() const {
        return this->sdd;
    }
    size_t get_ram() const {
        return this->ram;
    }

    bool get_is_bluetooth_enabled() const {
        return this->is_bluetooth_avaible;
    }

    bool get_is_graphics_card_enabled() const {
        return this->is_graphics_card_avaible;
    }
    // for printing test
    std::string toString() const {
        std::ostringstream oss;
        oss << "Sdd = " << sdd << '\n'
            << "Ram = " << ram << '\n'
            << "is Bluetooth Enabled: "
            << (is_bluetooth_avaible ? "true" : "false") << '\n'
            << "is graphics card enabled: "
            << (is_graphics_card_avaible ? "true" : "false") << '\n';
        return oss.str();

    }
};
int main() {
    
}
