#include "Collision.h"

bool Collision::IsColliding(const Rect& a, const Rect& b) {

    // eixo X
    if (a.pos.x + a.size.x < b.pos.x) return false;
    if (b.pos.x + b.size.x < a.pos.x) return false;

    // eixo Y
    if (a.pos.y + a.size.y < b.pos.y) return false;
    if (b.pos.y + b.size.y < a.pos.y) return false;

    return true;
}