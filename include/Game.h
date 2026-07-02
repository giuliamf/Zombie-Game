// declaração da classe
#pragma once

#include <string>
#include "SDL_include.h"
#include "State.h"
#include "StageState.h"

class Game {
public:
    static Game& GetInstance();

    SDL_Renderer* GetRenderer();
    State& GetState();
    void Run();

    ~Game();

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    StageState* state;
};