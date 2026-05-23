#include "InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() 
    :   quitRequested(false), 
        mouseX(0), 
        mouseY(0) {

    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = false;
    }
}

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

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseState[event.button.button] = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = false;
        }
    }
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
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
