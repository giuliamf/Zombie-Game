#include "Camera.h"
#include "InputManager.h"

Vec2 Camera::pos(0, 0);

void Camera::Update(float dt) {
    int speed = 300;

    if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
        pos.y -= speed * dt;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
        pos.y += speed * dt;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
        pos.x -= speed * dt;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
        pos.x += speed * dt;
    }
}