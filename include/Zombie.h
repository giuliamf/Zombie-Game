#pragma once

#include "Component.h"
#include "Timer.h"

class SpriteRenderer;

class Zombie : public Component {
public:
    Zombie(GameObject& associated);

    void Update(float dt) override;
    void Start() override;
    void NotifyCollision(GameObject& other) override;

    void NotifyHit();
    bool Is(std::string type) const override;

private:
    float lifeTime;
    SpriteRenderer* sprite;

    Timer deathTimer;
    bool isDead;
};