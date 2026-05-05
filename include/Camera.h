#pragma once

#include "Vec2.h"

class Camera {
public:
    static Vec2 pos;

    static void Update(float dt);
};