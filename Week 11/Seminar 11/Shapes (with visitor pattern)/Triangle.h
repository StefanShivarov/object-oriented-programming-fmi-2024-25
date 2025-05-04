#pragma once
#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);

    double getArea() const override;
    bool isPointInside(int x, int y) const override;

    bool intersectsWith(const Shape* other) const override;
    bool intersectsWithCircle(const Circle* circle) const override;
    bool intersectsWithTriangle(const Triangle* triangle) const override;
    bool intersectsWithRectangle(const Rectangle* rectangle) const override;
};
