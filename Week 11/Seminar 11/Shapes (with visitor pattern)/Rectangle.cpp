#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4) {
    setPoint(0, x1, y1);
    setPoint(1, x1, y3);
    setPoint(2, x3, y3);
    setPoint(3, x3, y1);
}

double Rectangle::getArea() const {
    double sideA = getPointAtIndex(0).getDistanceTo(getPointAtIndex(1));
    double sideB = getPointAtIndex(0).getDistanceTo(getPointAtIndex(3));

    return sideA * sideB;
}

bool Rectangle::isPointInside(int x, int y) const {
    Shape::Point p(x, y);
    return p.x >= getPointAtIndex(0).x
        && p.x >= getPointAtIndex(1).x
        && p.y <= getPointAtIndex(0).y
        && p.y >= getPointAtIndex(2).y;
}

bool Rectangle::intersectsWith(const Shape* other) const {
    return other->intersectsWithRectangle(this);
}

bool Rectangle::intersectsWithCircle(const Circle* circle) const {
    return circle->intersectsWithRectangle(this);
}

bool Rectangle::intersectsWithRectangle(const Rectangle* other) const {
    // TODO: add some geometric formula for rectangle intersection with rectangle
    throw std::logic_error("Not implemented");
}

bool Rectangle::intersectsWithTriangle(const Triangle* other) const {
    // TODO: add some geometric formula for rectangle intersection with triangle
    throw std::logic_error("Not implemented");
}
