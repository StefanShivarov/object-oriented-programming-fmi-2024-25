#include "Shape.h"
#include <assert.h>

Shape::Shape(size_t pointsCount) : pointsCount(pointsCount) {
    points = new Point[pointsCount];
}

Shape::Shape(const Shape& other) {
    copyFrom(other);
}

Shape::Shape(Shape&& other) noexcept {
    moveFrom(std::move(other));
}

Shape& Shape::operator=(const Shape& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Shape& Shape::operator=(Shape&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Shape::~Shape()
{
    free();
}

void Shape::setPoint(size_t index, int x, int y) {
    if (index >= pointsCount) {
        throw std::out_of_range("Index out of range!");
    }
    points[index].x = x;
    points[index].y = y;
}

double Shape::getPerimeter() const {
    assert(pointsCount >= 3);

    double perimeter = 0;
    for (size_t i = 0; i < pointsCount - 1; i++) {
        perimeter += points[i].getDistanceTo(points[i + 1]);
    }
    return perimeter + points[pointsCount - 1].getDistanceTo(points[0]);
}

const Shape::Point& Shape::getPointAtIndex(size_t index) const {
    if (index >= pointsCount) {
        throw std::out_of_range("Index out of range!");
    }
    return points[index];
}

void Shape::free() {
    delete[] points;
    points = nullptr;
    pointsCount = 0;
}

void Shape::copyFrom(const Shape& other) {
    points = new Point[other.pointsCount];
    for (size_t i = 0; i < other.pointsCount; i++) {
        points[i] = other.points[i];
    }
    pointsCount = other.pointsCount;
}

void Shape::moveFrom(Shape&& other) noexcept {
    points = other.points;
    other.points = nullptr;
    pointsCount = other.pointsCount;
    other.pointsCount = 0;
}
