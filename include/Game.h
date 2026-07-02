// declaração da classe
#pragma once

#include <string>
#include <stack>
#include <memory>
#include "SDL_include.h"
#include "State.h"

class Game {
public:
    static Game& GetInstance();

    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    void Push(State* state);
    void Run();

    ~Game();

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;

    std::stack<std::unique_ptr<State>> stateStack;
    State* storedState;
};
