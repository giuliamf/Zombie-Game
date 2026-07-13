#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <queue>
#include <memory>

class Character : public Component {
public:
    Character(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
    void SetSpeed(Vec2 dir);
    bool IsDead() const { return isDead; }
    bool Is(std::string type) const override;

private:
    Vec2 speed;
    float linearSpeed;
    int hp;
    std::weak_ptr<GameObject> gun;
    Timer damageTimer;
    bool isDead;
    float damageCooldown;
};