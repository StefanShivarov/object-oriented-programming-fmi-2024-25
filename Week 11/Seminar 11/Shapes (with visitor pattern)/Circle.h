#pragma once
#include "Shape.h"

class Circle : public Shape {
public:
    Circle(int x, int y, double radius);

    double getRadius() const;

    double getArea() const override;
    double getPerimeter() const override;
    bool isPointInside(int x, int y) const override;

    bool intersectsWith(const Shape* other) const override;
    bool intersectsWithCircle(const Circle* circle) const override;
    bool intersectsWithTriangle(const Triangle* triangle) const override;
    bool intersectsWithRectangle(const Rectangle* rectangle) const override;

private:
    double radius;
};
