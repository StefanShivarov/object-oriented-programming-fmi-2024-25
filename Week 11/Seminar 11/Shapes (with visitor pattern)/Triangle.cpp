#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3) {
    setPoint(0, x1, y1);
    setPoint(1, x2, y2);
    setPoint(2, x3, y3);
}

double Triangle::getArea() const {
    double sideA = getPointAtIndex(0).getDistanceTo(getPointAtIndex(1));
    double sideB = getPointAtIndex(0).getDistanceTo(getPointAtIndex(2));
    double sideC = getPointAtIndex(1).getDistanceTo(getPointAtIndex(2));

    double halfPer = getPerimeter() / 2;

    return sqrt(halfPer * (halfPer - sideA) * (halfPer - sideB) * (halfPer - sideC));
}

bool Triangle::isPointInside(int x, int y) const {
    Shape::Point p(x, y);
    Triangle t1(getPointAtIndex(0).x, getPointAtIndex(0).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
    Triangle t2(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
    Triangle t3(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(0).x, getPointAtIndex(0).y, p.x, p.y);

    return abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}

bool Triangle::intersectsWith(const Shape* other) const {
    return other->intersectsWithTriangle(this);
}

bool Triangle::intersectsWithCircle(const Circle* circle) const {
    return circle->intersectsWithTriangle(this);
}

bool Triangle::intersectsWithRectangle(const Rectangle* rectangle) const {
    return rectangle->intersectsWithTriangle(this);
}

bool Triangle::intersectsWithTriangle(const Triangle* triangle) const {
    // TODO: add some geometric formula about triangle intersection with triangle
    throw std::logic_error("Not implemented");
}
