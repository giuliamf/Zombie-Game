#pragma once

#include "Vec2.h"

class Rect {
public:
    Vec2 pos;
    Vec2 size;

    Rect();
    Rect(float x, float y, float w, float h);
};