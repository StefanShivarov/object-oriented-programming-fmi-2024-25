#include "Factory.h"
#include "OOP.h"
#include "Dis.h"
#include "DSTR2.h"
#include "UP.h"
#include "Geometry.h"
Subject* subjectFactory(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass,int bonus)
{
    if (strcmp(subject, "OOP")==0)
    {
        return new OOP(subject, lector, asistentNames, size, pointsToPass, bonus);
    }
    if (strcmp(subject, "DIS") == 0) {
        return new Dis(subject, lector, asistentNames, size, pointsToPass);
    }
    if (strcmp(subject, "DSTR") == 0) {
        return new DSTR2(subject, lector, asistentNames, size, pointsToPass);
    }
    if (strcmp(subject, "UP") == 0) {
        return new UP(subject, lector, asistentNames, size, pointsToPass);
    }
    if (strcmp(subject, "Geometry") == 0) {
        return new Geometry(subject, lector, asistentNames, size, pointsToPass);
    }
    return nullptr;
}
