#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"

const double PI = 3.1415;

Circle::Circle(int x, int y, double radius) : Shape(1), radius(radius) {
    setPoint(0, x, y);
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getArea() const {
    return PI * radius * radius;
}

double Circle::getPerimeter() const {
    return 2 * PI * radius;
}

bool Circle::isPointInside(int x, int y) const {
    Shape::Point point(x, y);
    return point.getDistanceTo(getPointAtIndex(0)) <= radius;
}

bool Circle::intersectsWith(const Shape* other) const {
    return other->intersectsWithCircle(this);
}

bool Circle::intersectsWithCircle(const Circle* circle) const {
    const Point& a = getPointAtIndex(0);
    const Point& b = circle->getPointAtIndex(0);

    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double distSq = dx * dx + dy * dy;
    double rSum = radius + circle->radius;

    return distSq <= rSum * rSum;
}

bool Circle::intersectsWithRectangle(const Rectangle* rectangle) const {
    // TODO: add some geometric formula about circle intersection with rectangle
    throw std::logic_error("Not implemented");
}

bool Circle::intersectsWithTriangle(const Triangle* triangle) const {
    // TODO: add some geometric formula about circle intersection with triangle
    throw std::logic_error("Not implemented");
}
