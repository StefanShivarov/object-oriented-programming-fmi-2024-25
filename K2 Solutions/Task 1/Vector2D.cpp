#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

double Vector2D::getX() const {
    return x;
}

double Vector2D::getY() const {
    return y;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
    return Vector2D(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY());

    /* or alternatively you can reuse the operator+= :
    Vector2D result(lhs);
    result += rhs;
    return result;
    */
}

Vector2D operator*(double n, const Vector2D& vector) {
    return Vector2D(n * vector.x, n * vector.y);
}

Vector2D operator*(const Vector2D& vector, double n) {
    return n * vector;
}

double operator^(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.getX() * rhs.getX() + lhs.getY() * rhs.getY();
}

bool operator==(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Vector2D& lhs, const Vector2D& rhs) {
    return !(lhs == rhs);
}
