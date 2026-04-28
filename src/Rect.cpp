#include "Rect.h"

Rect::Rect()
    : pos(0, 0), size(0, 0)
{
}

Rect::Rect(float x, float y, float w, float h)
    : pos(x, y), size(w, h)
{
}
