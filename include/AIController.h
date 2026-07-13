#pragma once

#include "Component.h"
#include "Vec2.h"

class GameObject;

class AIController : public Component {
public:
    AIController(GameObject& associated, float linearSpeed = 100.0f);

    void Start() override;
    void Update(float dt) override;
    bool Is(std::string type) const override;

    void SetLinearSpeed(float speed);

private:
    void FindTarget();
    void MoveTowardsTarget(float dt);

    GameObject* target;
    float linearSpeed;
};

// Made with Bob
