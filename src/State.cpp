#include "State.h"
#include <SDL2/SDL.h>

// começa sem o request de saída
State::State()
    : quitRequested(false)
{
    LoadAssets();
}

// carrega os recursos e deixa pronto na memória
void State::LoadAssets() {
    bg.Open("Resources/img/background.png");

    // carrega a música e dá play em loop infinito
    music.Open("Resources/audio/BGM.wav");
    music.Play();
}

// vira true se o jogador apertou altf4 ou no X
void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

// (x,y) = (0,0)
void State::Render() {
    bg.Render(0, 0);
}

// definir se pode fechar o jogo
bool State::QuitRequested() {
    return quitRequested;
}