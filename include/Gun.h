#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <memory>

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> character);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

private:
    std::weak_ptr<GameObject> character;
    float angle;
    Timer cooldownTimer;
    float cooldownTime;
};