#pragma once

#include "Rect.h"

class Collision {
public:
    static bool IsColliding(const Rect& a, const Rect& b);
};