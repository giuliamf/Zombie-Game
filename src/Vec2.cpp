#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
    : x(0), y(0)
{
}

Vec2::Vec2(float x, float y)
    : x(x), y(y)
{
}

// Operadores
Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

// Métodos utilitários
float Vec2::GetMagnitude() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::GetNormalized() const {
    float mag = GetMagnitude();
    if (mag == 0) {
        return Vec2(0, 0);
    }
    return Vec2(x / mag, y / mag);
}
