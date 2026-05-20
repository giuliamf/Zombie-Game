#pragma once

#include <unordered_map>
#include "SDL_include.h"

class InputManager {
public:
    static InputManager& GetInstance();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool QuitRequested();

    int GetMouseX() const;
    int GetMouseY() const;

private:
    InputManager();
    std::unordered_map<int, bool> keyState;
    bool quitRequested;

    int mouseX;
    int mouseY;

};