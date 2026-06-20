#pragma once

#include <cmath>

class Vec2 {
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    // Operadores
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
    Vec2& operator+=(const Vec2& other);

    // Métodos utilitários
    float GetMagnitude() const;
    Vec2 GetNormalized() const;
};