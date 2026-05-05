#pragma once

#include <map>
#include <string>
#include "Component.h"
#include "Animation.h"

class SpriteRenderer;

class Animator : public Component {
public:
    Animator(GameObject& associated);

    void Update(float dt) override;

    void AddAnimation(const std::string& name, Animation animation);
    void SetAnimation(const std::string& name);
    
    void Stop();

private:
    bool active;
    std::map<std::string, Animation> animations;

    SpriteRenderer* sprite;
    Animation* currentAnimation;

    float timeElapsed;
    int currentFrame;
};