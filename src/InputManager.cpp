#include "InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : quitRequested(false), mouseX(0), mouseY(0) {}

void InputManager::Update() {
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }

        if (event.type == SDL_KEYDOWN) {
            keyState[event.key.keysym.sym] = true;
        }

        if (event.type == SDL_KEYUP) {
            keyState[event.key.keysym.sym] = false;
        }
    }
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::KeyPress(int key) {
    return keyState[key];
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key];
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}
