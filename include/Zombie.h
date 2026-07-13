#pragma once

#include "Component.h"
#include "Timer.h"

class SpriteRenderer;

class Zombie : public Component {
public:
    Zombie(GameObject& associated);

    void Update(float dt) override;
    void Start() override;

    void NotifyHit();

private:
    float lifeTime;
    SpriteRenderer* sprite;

    Timer deathTimer;
    bool isDead;
};