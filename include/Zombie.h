#pragma once

#include "Component.h"
#include "Timer.h"

class SpriteRenderer;

class Zombie : public Component {
public:
    Zombie(GameObject& associated);

    void Update(float dt) override;

private:
    float lifeTime;
    SpriteRenderer* sprite;

    Timer deathTimer;
    bool isDead;
};