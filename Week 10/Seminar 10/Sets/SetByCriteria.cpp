#include "SetByCriteria.h"

SetByCriteria::SetByCriteria(bool (*accepts)(unsigned), bool (*rejects)(unsigned)) : criteria{accepts, rejects} {}

void SetByCriteria::add(unsigned n) {
    if (criteria.accepts(n) && !criteria.rejects(n)) {
        Bitset::add(n);
    }
}

void SetByCriteria::setAcceptsCriteria(bool (*accepts)(unsigned)) {
    criteria.accepts = accepts;
    for (size_t i = 0; i < bytesCount * 8; i++) {
        if (contains(i) && !criteria.accepts(i)) {
            remove(i);
        }
    }
}

void SetByCriteria::setRejectsCriteria(bool (*rejects)(unsigned)) {
    criteria.rejects = rejects;
    for (size_t i = 0; i < bytesCount * 8; i++) {
        if (contains(i) && criteria.rejects(i)) {
            remove(i);
        }
    }
}
