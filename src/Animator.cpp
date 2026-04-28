#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(GameObject& associated)
    : Component(associated),
      sprite(nullptr),
      currentAnimation(nullptr),
      timeElapsed(0.0f),
      currentFrame(0)
{
    for (auto component : associated.GetComponents()) {
        sprite = dynamic_cast<SpriteRenderer*>(component);
        if (sprite != nullptr)
            break;
    }
}

void Animator::AddAnimation(const std::string& name, Animation animation) {
    animations.emplace(name, animation);
}


void Animator::SetAnimation(const std::string& name) {
    auto it = animations.find(name);

    if (it == animations.end())
        return;

    currentAnimation = &it->second;
    currentFrame = currentAnimation->frameStart;
    timeElapsed = 0.0f;

    if (sprite != nullptr) {
        sprite->sprite.SetFrame(currentFrame);
    }
}

void Animator::Update(float dt) {
    if (currentAnimation == nullptr || sprite == nullptr)
        return;

    timeElapsed += dt;

    if (timeElapsed >= currentAnimation->frameTime) {
        timeElapsed = 0.0f;
        currentFrame++;

        if (currentFrame > currentAnimation->frameEnd) {
            currentFrame = currentAnimation->frameStart;
        }

        sprite->sprite.SetFrame(currentFrame);
    }
}