#include "Singleton.h"

Singleton& Singleton::getInstance() {
    static Singleton singleton;
    return singleton;
}
