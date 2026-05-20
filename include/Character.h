#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <queue>

class Character : public Component {
public:
    Character(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

private:
    Vec2 speed;
    float linearSpeed;
    int hp;
};