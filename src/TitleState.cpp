#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "StageState.h"

#include <SDL2/SDL.h>

TitleState::TitleState() {
    LoadAssets();

    // Fundo com a imagem de título
    GameObject* bg = new GameObject();
    bg->box.pos.x = 0;
    bg->box.pos.y = 0;
    bg->AddComponent(
        new SpriteRenderer(
            *bg,
            "Resources/img/Title.png"
        )
    );

    AddObject(bg);
}

TitleState::~TitleState() {
}

void TitleState::LoadAssets() {
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}

void TitleState::Update(float dt) {
    // Fechar janela pelo botão X
    if (SDL_QuitRequested()) {
        quitRequested = true;
        return;
    }

    InputManager& input = InputManager::GetInstance();

    // ESC — encerra o jogo
    if (input.IsKeyDown(SDLK_ESCAPE)) {
        quitRequested = true;
        return;
    }

    // SPACE — inicia o jogo
    if (input.IsKeyDown(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }

    UpdateArray(dt);
}

void TitleState::Render() {
    RenderArray();
}
