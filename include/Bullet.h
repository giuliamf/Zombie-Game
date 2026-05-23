#pragma once

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    // construtor
    Bullet(GameObject& associated, float angle, float speed, float maxDistance);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

private:
    Vec2 speedVec;       // direção e velocidade da bala
    float distanceLeft;  // quanto ainda pode andar
};