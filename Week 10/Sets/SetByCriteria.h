#pragma once
#include "Bitset.h"

class SetByCriteria : public Bitset {

public:
    SetByCriteria(bool (*accepts)(unsigned) = [](unsigned n){ return true; },
        bool (*rejects)(unsigned) = [](unsigned n){ return false; });

    void setAcceptsCriteria(bool (*accepts)(unsigned));
    void setRejectsCriteria(bool (*rejects)(unsigned));

    void add(unsigned n);

private:
    struct Criteria {
        bool (*accepts)(unsigned n);
        bool (*rejects)(unsigned n);
    } criteria;
};
