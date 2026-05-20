#pragma once

#include "Component.h"

class PlayerController : public Component {
public:
    PlayerController(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
};
