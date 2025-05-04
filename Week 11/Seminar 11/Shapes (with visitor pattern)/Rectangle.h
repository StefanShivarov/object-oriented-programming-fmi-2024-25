#pragma once
#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(int x1, int y1, int x3, int y3);

    double getArea() const override;
    bool isPointInside(int x, int y) const override;

    bool intersectsWith(const Shape* other) const override;
    bool intersectsWithCircle(const Circle* circle) const override;
    bool intersectsWithTriangle(const Triangle* triangle) const override;
    bool intersectsWithRectangle(const Rectangle* rectangle) const override;
};
