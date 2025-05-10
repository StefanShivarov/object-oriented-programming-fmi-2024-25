#pragma once

class Vector2D {
public:
    Vector2D() = default;
    Vector2D(double x, double y);

    double getX() const;
    double getY() const;

    Vector2D& operator+=(const Vector2D& other);
    friend Vector2D operator*(double n, const Vector2D& vector);

private:
    double x = 0.0;
    double y = 0.0;
};

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator*(const Vector2D& vector, double n);
double operator^(const Vector2D& lhs, const Vector2D& rhs);
bool operator==(const Vector2D& lhs, const Vector2D& rhs);
bool operator!=(const Vector2D& lhs, const Vector2D& rhs);
