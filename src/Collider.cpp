#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset) {}


void Collider::Update(float dt) {

    box = associated.box;

    // escala
    box.size.x *= scale.x;
    box.size.y *= scale.y;

    // centro
    float centerX = associated.box.pos.x + associated.box.size.x / 2;
    float centerY = associated.box.pos.y + associated.box.size.y / 2;

    // aplica offset
    float newCenterX = centerX + offset.x;
    float newCenterY = centerY + offset.y;

    // reposiciona box
    box.pos.x = newCenterX - box.size.x / 2;
    box.pos.y = newCenterY - box.size.y / 2;
}

bool Collider::Is(std::string type) const {
    return type == "Collider";
}

void Collider::Render() {
}